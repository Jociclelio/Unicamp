def main() -> None:
    matrix_comodo = [input().split() for _ in range(int(input()))]
    robo = Robo_limpeza(
        matrix_comodo, (len(matrix_comodo), len(matrix_comodo[0]))
    )
    print(robo)
    while robo.passo():
        print()
        print(robo)


class Robo_limpeza:
    def __init__(
        self, matrix_comodo: list[list[str]], dimensoes: tuple[int, int]
    ):
        self.matrix_comodo = matrix_comodo
        self.dimensoes = dimensoes
        self.modo = "Escaneamento do ambiente"
        linha_robo = [linha.count("r") for linha in matrix_comodo].index(1)
        self.posicao_robo: tuple[int, int] = (
            linha_robo,
            matrix_comodo[linha_robo].index("r"),
        )
        self.visao = self.ver()
        self.ponto_de_retorno: tuple[int, ...] = (int(), int())
        self.ligado: bool = True

    def passo(self) -> bool:
        self.visao = self.ver()
        # print(self.modo)
        match self.modo:
            case "Escaneamento do ambiente":
                self.escaneamento_ambiente()
            case "Limpando":
                self.limpando()
            case "Retornar ao escaneamento do ambiente":
                self.retornar_ao_escaneamento_do_ambiente()
            case "Finalizar limpeza":
                self.finalizar_limpeza()
        return self.ligado

    def direcao_escaneamento(self, ponto: tuple[int, ...]) -> str:
        esquerda, _, direita, _ = self.visao
        limite_linha, _ = self.dimensoes
        pos_robo_linha, _ = ponto
        eh_linha_par: bool = pos_robo_linha % 2 == 0
        if eh_linha_par and direita:
            return "direita"
        elif not (eh_linha_par) and esquerda:
            return "esquerda"
        elif pos_robo_linha + 1 < limite_linha:
            return "baixo"
        return ""

    def escaneamento_ambiente(self) -> None:
        direcao = self.direcao_escaneamento(self.posicao_robo)
        if "o" in self.visao:
            # print(self.modo, " -> ", "Limpando")
            self.ponto_de_retorno = tuple(self.posicao_robo)
            self.modo = "Limpando"
            self.limpando()
        elif direcao:
            self.mover(direcao)
        else:
            self.modo = "Finalizar limpeza"
            self.finalizar_limpeza()

    def limpando(self) -> None:
        _, direcao = self.acao(
            self.direcao_escaneamento(self.ponto_de_retorno),
            self.ponto_de_retorno,
        )
        # print(self.ponto_de_retorno)
        # print(self.direcao_escaneamento(self.ponto_de_retorno))
        # print(direcao)
        # print(self.posicao_robo)
        if direcao == self.posicao_robo:
            print(self.modo, " -> ", "Escaneamento do ambiente")
            self.modo = "Escaneamento do ambiente"
            self.escaneamento_ambiente()
        elif "o" in self.visao:
            match self.visao.index("o"):
                case 0:
                    self.mover("esquerda")
                case 1:
                    self.mover("cima")
                case 2:
                    self.mover("direita")
                case 3:
                    self.mover("baixo")
        else:
            self.modo = "Retornar ao escaneamento do ambiente"
            self.retornar_ao_escaneamento_do_ambiente()

    def retornar_ao_escaneamento_do_ambiente(self) -> None:
        pos_robo_linha, pos_robo_coluna = self.posicao_robo
        pos_retorno_linha, pos_retorno_coluna = self.ponto_de_retorno
        if "o" in self.visao:
            # print(self.modo, " -> ", "Limpando")
            self.modo = "Limpando"
            self.limpando()
        else:
            if pos_robo_coluna != pos_retorno_coluna:
                if pos_robo_coluna > pos_retorno_coluna:
                    self.mover("esquerda")
                else:
                    self.mover("direita")
            elif pos_robo_linha != pos_retorno_linha:
                if pos_robo_linha > pos_retorno_linha:
                    self.mover("cima")
                else:
                    self.mover("baixo")
            else:
                # print(self.modo, " -> ", "Escaneamento do ambiente")
                self.modo = "Escaneamento do ambiente"
                self.escaneamento_ambiente()

    def finalizar_limpeza(self) -> None:
        _, pos_robo_coluna = self.posicao_robo
        _, limite_coluna = self.dimensoes
        if pos_robo_coluna + 1 < limite_coluna:
            self.mover("direita")
        else:
            self.modo = "Desligar"
            self.ligado = False

    def ver(self) -> tuple[str, ...]:
        direcoes = ["esquerda", "cima", "direita", "baixo"]
        return tuple(self.ver_direcao(direcao) for direcao in direcoes)

    def ver_direcao(self, direcao: str) -> str:
        eh_possivel_ver, (pos_ver_linha, pos_ver_coluna) = self.acao(
            direcao, self.posicao_robo
        )
        if eh_possivel_ver:
            return self.matrix_comodo[pos_ver_linha][pos_ver_coluna]
        return ""

    def mover(self, direcao: str) -> bool:
        pos_robo_linha, pos_robo_coluna = self.posicao_robo
        eh_possivel_mover, (pos_mover_linha, pos_mover_coluna) = self.acao(
            direcao, self.posicao_robo
        )
        if eh_possivel_mover:
            self.matrix_comodo[pos_robo_linha][pos_robo_coluna] = "."
            self.matrix_comodo[pos_mover_linha][pos_mover_coluna] = "r"
            self.posicao_robo = (pos_mover_linha, pos_mover_coluna)
            return True
        return False

    def acao(
        self, direcao: str, posicao_acao: tuple[int, ...]
    ) -> tuple[bool, tuple[int, int]]:
        limite_linha, limite_coluna = self.dimensoes
        pos_acao_linha, pos_acao_coluna = posicao_acao
        eh_possivel_acao: bool = False
        match direcao:
            case "direita":
                pos_acao_coluna += 1
                eh_possivel_acao = pos_acao_coluna < limite_coluna
            case "esquerda":
                pos_acao_coluna -= 1
                eh_possivel_acao = pos_acao_coluna >= 0
            case "cima":
                pos_acao_linha -= 1
                eh_possivel_acao = pos_acao_linha >= 0
            case "baixo":
                pos_acao_linha += 1
                eh_possivel_acao = pos_acao_linha < limite_linha
        return (eh_possivel_acao, (pos_acao_linha, pos_acao_coluna))

    def __str__(self) -> str:
        return "\n".join([" ".join(linha) for linha in self.matrix_comodo])


main() if __name__ == "__main__" else None
