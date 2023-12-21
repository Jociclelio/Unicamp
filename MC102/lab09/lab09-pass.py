from typing import Callable


def main() -> None:
    matriz_comodo: list[list[str]] = [
        input().split() for _ in range(int(input()))
    ]
    robo: Robo_limpeza = Robo_limpeza(matriz_comodo)
    print(robo)
    while robo.passo():
        print()
        print(robo)


class Robo_limpeza:
    def __init__(self, matriz_comodo: list[list[str]]):
        self.matriz_comodo: list[list[str]] = matriz_comodo
        self.limites_comodo: tuple[int, int] = (
            len(matriz_comodo) - 1,
            len(matriz_comodo[0]) - 1,
        )
        self.posicao_robo: tuple[int, int] = (0, 0)
        self.esta_ligado: bool = True
        self.modo: str = "Escaneamento do ambiente"
        self.modos: dict[str, Callable[[], None]] = {
            "Escaneamento do ambiente": self.escaneamento_ambiente,
            "Limpando": self.limpando,
            "Retornar ao escaneamento do ambiente": self.retorn_escan_amb,
            "Finalizar limpeza": self.finalizar_limpeza,
        }
        self.ponto_de_retorno: tuple[int, ...] = (int(), int())
        self.direcoes: dict[str, tuple[int, int]] = {
            "esquerda": (0, -1),
            "cima": (-1, 0),
            "direita": (0, 1),
            "baixo": (1, 0),
        }
        self.visao: tuple[str, ...] = self.ver(self.posicao_robo)

    def passo(self) -> bool:
        self.visao = self.ver(self.posicao_robo)
        self.modos[self.modo]()
        return self.esta_ligado

    def trocar_modo(self, novo_modo: str) -> None:
        self.modo = novo_modo
        self.passo()

    def direcao_escaneamento(self, ponto: tuple[int, ...]) -> tuple[int, ...]:
        """função direção escaneamento retorna a direção
        do escaneamento em um ponto na matriz caso"""
        str_esquerda, _, str_direita, str_baixo = self.ver(ponto)
        pos_linha, _ = ponto
        eh_linha_par: bool = pos_linha % 2 == 0
        if eh_linha_par and str_direita:
            return self.direcoes["direita"]
        elif not (eh_linha_par) and str_esquerda:
            return self.direcoes["esquerda"]
        elif str_baixo:
            return self.direcoes["baixo"]
        return ()

    def escaneamento_ambiente(self) -> None:
        direcao = self.direcao_escaneamento(self.posicao_robo)
        if "o" in self.visao:
            self.ponto_de_retorno = tuple(self.posicao_robo)
            self.trocar_modo("Limpando")
        elif direcao:
            self.mover(direcao)
        else:
            self.trocar_modo("Finalizar limpeza")

    def limpando(self) -> None:
        proxima_posicao_escaneamento = tuple(
            pos_ponto_de_retorno + pos_direcao
            for pos_ponto_de_retorno, pos_direcao in zip(
                self.ponto_de_retorno,
                self.direcao_escaneamento(self.ponto_de_retorno),
            )
        )
        if proxima_posicao_escaneamento == self.posicao_robo:
            self.trocar_modo("Escaneamento do ambiente")
        elif "o" in self.visao:
            self.mover(
                self.direcoes[
                    list(self.direcoes.keys())[self.visao.index("o")]
                ]
            )
        else:
            self.trocar_modo("Retornar ao escaneamento do ambiente")

    def retorn_escan_amb(self) -> None:
        pos_robo_linha, pos_robo_coluna = self.posicao_robo
        pos_retorno_linha, pos_retorno_coluna = self.ponto_de_retorno
        if "o" in self.visao:
            self.trocar_modo("Limpando")
        elif self.posicao_robo != self.ponto_de_retorno:
            if pos_robo_coluna != pos_retorno_coluna:
                if pos_robo_coluna > pos_retorno_coluna:
                    self.mover(self.direcoes["esquerda"])
                else:
                    self.mover(self.direcoes["direita"])
            elif pos_robo_linha != pos_retorno_linha:
                if pos_robo_linha > pos_retorno_linha:
                    self.mover(self.direcoes["cima"])
                else:
                    self.mover(self.direcoes["baixo"])
        else:
            self.trocar_modo("Escaneamento do ambiente")

    def finalizar_limpeza(self) -> None:
        _, pos_robo_coluna = self.posicao_robo
        _, limite_coluna = self.limites_comodo
        if pos_robo_coluna < limite_coluna:
            self.mover(self.direcoes["direita"])
        else:
            self.esta_ligado = False

    def ver(self, ponto: tuple[int, ...]) -> tuple[str, ...]:
        pos_linha, pos_coluna = ponto
        limite_linha, limite_coluna = self.limites_comodo
        return tuple(
            self.matriz_comodo[pos_linha + direcao_linha][
                pos_coluna + direcao_coluna
            ]
            if (0 <= pos_linha + direcao_linha <= limite_linha)
            and (0 <= pos_coluna + direcao_coluna <= limite_coluna)
            else ""
            for direcao_linha, direcao_coluna in self.direcoes.values()
        )

    def mover(self, direcao: tuple[int, ...]) -> None:
        posicao_mover = tuple(
            pos_robo + pos_mover
            for pos_robo, pos_mover in zip(self.posicao_robo, direcao)
        )
        # if [
        #     None
        #     for pos_mover, limite in zip(posicao_mover, self.limites_comodo)
        #     if 0 <= pos_mover <= limite
        # ]:
        pos_robo_linha, pos_robo_coluna = self.posicao_robo
        pos_mover_linha, pos_mover_coluna = posicao_mover
        self.matriz_comodo[pos_robo_linha][pos_robo_coluna] = "."
        self.matriz_comodo[pos_mover_linha][pos_mover_coluna] = "r"
        self.posicao_robo = (pos_mover_linha, pos_mover_coluna)

    def __str__(self) -> str:
        return "\n".join([" ".join(linha) for linha in self.matriz_comodo])


main() if __name__ == "__main__" else None
