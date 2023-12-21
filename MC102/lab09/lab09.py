from typing import Callable


def main() -> None:
    # Início Entrada
    matriz_comodo: list[list[str]] = [
        input().split() for _ in range(int(input()))
    ]
    # Fim Entrada

    # Instânciando robô de limpeza (por padrão ele vem ligado)
    robo: Robo_limpeza = Robo_limpeza(matriz_comodo)

    # Executa Limpeza (aqui usaria um do while se existisse no python :/)
    print(robo)
    while robo.passo():
        print()
        print(robo)


class Robo_limpeza:
    def __init__(self, matriz_comodo: list[list[str]]):
        """
        Define os atributos iniciais e padrões do robô
        """

        # Salva a matriz_cômodo
        self._matriz_comodo: list[list[str]] = matriz_comodo

        # Define o limites da Matriz, nesse caso o ultimo indice válido
        self._limites_comodo: tuple[int, int] = (
            len(matriz_comodo) - 1,
            len(matriz_comodo[0]) - 1,
        )

        # Define a posição do robô na matriz (sempre iniciando o ponto (0,0))
        self._posicao_robo: tuple[int, int] = (0, 0)

        # Define o estado de operação do robô (por padrão é ligado)
        self._esta_ligado: bool = True

        # Define o modo incial (Escaneamento do ambiente)
        self._modo: str = "Escaneamento do ambiente"

        # Dicionario dos modos do robô (não tem o autodestruição)
        self._modos: dict[str, Callable[[], None]] = {
            "Escaneamento do ambiente": self._escaneamento_ambiente,
            "Limpando": self._limpando,
            "Retornar ao escaneamento do ambiente": self._retorn_escan_amb,
            "Finalizar limpeza": self._finalizar_limpeza,
        }

        # Dicionario de direções (melhoram a leitura do código)
        self._direcoes: dict[str, tuple[int, int]] = {
            "esquerda": (0, -1),
            "cima": (-1, 0),
            "direita": (0, 1),
            "baixo": (1, 0),
        }
        # Declara a variável ponto de retorno, usada quando se muda
        # do modo escaneamento do ambiente para o modo limpar
        self._ponto_de_retorno: tuple[int, ...] = (int(), int())

    def passo(self) -> bool:
        """
        Executa o proximo passo do robô e estiver ligado
        Retorna se o robô esta ligado ou não
        """
        if self._esta_ligado:
            self._visao = self._ver(self._posicao_robo)
            self._modos[self._modo]()
        return self._esta_ligado

    def _trocar_modo(self, novo_modo: str) -> None:
        """Troca o modo do robô e executa o proximo passo"""
        self._modo = novo_modo
        self.passo()

    def _direcao_escaneamento(self, ponto: tuple[int, ...]) -> tuple[int, ...]:
        """
        Função direção escaneamento retorna a direção (tupla de inteiros)
        do escaneamento em um ponto na matriz
        """
        str_esquerda, _, str_direita, str_baixo = self._ver(ponto)
        pos_linha, _ = ponto
        eh_linha_par: bool = pos_linha % 2 == 0
        if eh_linha_par and str_direita:
            return self._direcoes["direita"]
        elif not (eh_linha_par) and str_esquerda:
            return self._direcoes["esquerda"]
        elif str_baixo:
            return self._direcoes["baixo"]
        return ()

    def _escaneamento_ambiente(self) -> None:
        """
        Executa proximo passo na direção do escaneamento,
        muda de modo caso:
            encontre uma sujeira adjacente -> Limpando
            chege no final do escaneamento -> Finalizar limpeza
        """
        direcao: tuple[int, ...] = self._direcao_escaneamento(
            self._posicao_robo
        )
        if "o" in self._visao:
            self._ponto_de_retorno = tuple(self._posicao_robo)
            self._trocar_modo("Limpando")
        elif direcao:
            self._mover(direcao)
        else:
            self._trocar_modo("Finalizar limpeza")

    def _limpando(self) -> None:
        """Executa o moviento a sujeira adjacente
        caso não tenho muda de modo caso:
            (a posição atual é a proxima posição
            do escaneamento do ambiente) -> Escaneamento do ambiente
            caso contrário -> Retornar ao escaneamento do ambiente
        """
        proxima_posicao_escaneamento = tuple(
            pos_ponto_de_retorno + pos_direcao
            for pos_ponto_de_retorno, pos_direcao in zip(
                self._ponto_de_retorno,
                self._direcao_escaneamento(self._ponto_de_retorno),
            )
        )
        if proxima_posicao_escaneamento == self._posicao_robo:
            self._trocar_modo("Escaneamento do ambiente")
        elif "o" in self._visao:
            direcao = list(self._direcoes.values())[
                list(self._visao).index("o")
            ]
            self._mover(direcao)
        else:
            self._trocar_modo("Retornar ao escaneamento do ambiente")

    def _retorn_escan_amb(self) -> None:
        """
        Retorna para o ponto de retorno
        muda de modo caso:
            sujeira adjacente -> Limpando
            chege no ponto de retorno -> Escaneamento do ambiente
        """
        if "o" in self._visao:
            self._trocar_modo("Limpando")
        elif self._posicao_robo != self._ponto_de_retorno:
            pos_robo_linha, pos_robo_coluna = self._posicao_robo
            pos_retorno_linha, pos_retorno_coluna = self._ponto_de_retorno
            if pos_robo_coluna != pos_retorno_coluna:
                if pos_robo_coluna > pos_retorno_coluna:
                    self._mover_str("esquerda")
                else:
                    self._mover_str("direita")
            else:
                if pos_robo_linha > pos_retorno_linha:
                    self._mover_str("cima")
                else:
                    self._mover_str("baixo")
        else:
            self._ponto_de_retorno = (int(), int())
            self._trocar_modo("Escaneamento do ambiente")

    def _finalizar_limpeza(self) -> None:
        """
        Move em direção ao úlimo índice da matriz( canto inferior direito )
        onde as somas do indíces a maior e toda a matriz
        Quando chega, desliga o robô
        """
        _, pos_robo_coluna = self._posicao_robo
        _, limite_coluna = self._limites_comodo
        if pos_robo_coluna < limite_coluna:
            self._mover_str("direita")
        else:
            self._esta_ligado = False

    def _ver(self, ponto: tuple[int, ...]) -> tuple[str, ...]:
        """
        Verifica os indíces ao redor de um ponto
        e retorna eles em uma tupla de strings
        na ordem (esquerda, cima, direita, baixo)
        """
        pos_linha, pos_coluna = ponto
        limite_linha, limite_coluna = self._limites_comodo
        return tuple(
            self._matriz_comodo[pos_linha + direcao_linha][
                pos_coluna + direcao_coluna
            ]
            if (0 <= pos_linha + direcao_linha <= limite_linha)
            and (0 <= pos_coluna + direcao_coluna <= limite_coluna)
            else ""
            for direcao_linha, direcao_coluna in self._direcoes.values()
        )

    def _mover_str(self, direcao: str) -> None:
        """
        Move o robo em uma direcao de acordo com uma
        string, caso a string nao indique uma direcao
        o robo moverar para sua propria posicao
        """
        self._mover(self._direcoes.get(direcao, (0, 0)))

    def _mover(self, direcao: tuple[int, ...]) -> None:
        """
        Move o robô em uma posição de acordo com
        a direção passada pro parâmetro
        """
        # Calcula a nova posição do robo na matriz
        pos_mover_linha, pos_mover_coluna = tuple(
            pos_robo + pos_mover
            for pos_robo, pos_mover in zip(self._posicao_robo, direcao)
        )

        # Verifica se a nova posição é um indice válido na matriz
        limite_linha, limite_coluna = self._limites_comodo
        if pos_mover_linha > limite_linha or pos_mover_coluna > limite_coluna:
            return

        # Move o robo para a posicão nova
        pos_robo_linha, pos_robo_coluna = self._posicao_robo
        self._matriz_comodo[pos_robo_linha][pos_robo_coluna] = "."
        self._matriz_comodo[pos_mover_linha][pos_mover_coluna] = "r"
        self._posicao_robo = (pos_mover_linha, pos_mover_coluna)

    def __str__(self) -> str:
        """
        Printa a matriz_comodo formatada
        """
        return "\n".join([" ".join(linha) for linha in self._matriz_comodo])


main() if __name__ == "__main__" else None
