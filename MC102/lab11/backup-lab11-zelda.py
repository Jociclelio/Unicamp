from typing import Any, Callable

# Início Main


def main() -> None:
    # Início Entrada
    zelda_vida_inicial, zelda_ataque_inicial = map(int, input().split())
    masmorra_dimensoes: tuple[int, ...] = tuple(map(int, input().split()))
    zelda_posicao: tuple[int, ...] = tuple(map(int, input().split(",")))
    masmorra_pos_saida: tuple[int, ...] = tuple(map(int, input().split(",")))

    zelda: Zelda = Zelda(
        "P",
        zelda_posicao,
        zelda_vida_inicial,
        zelda_ataque_inicial,
    )

    saida: SaidaMasmorra = SaidaMasmorra("*", masmorra_pos_saida)

    monstros: list[Monstro] = [
        Monstro(
            tipo,
            tuple(
                map(
                    int,
                    posicao.split(","),
                )
            ),
            int(vida),
            int(ataque),
        )
        for vida, ataque, tipo, posicao in [
            input().split() for _ in range(int(input()))
        ]
    ]

    items: list[Item] = [
        Item(
            tipo,
            tuple(map(int, posicao.split(","))),
            nome_item,
            int(status),
        )
        for nome_item, tipo, posicao, status in [
            input().split() for _ in range(int(input()))
        ]
    ]
    # Fim Entrada

    masmorra: Masmorra = Masmorra(
        masmorra_dimensoes,
        saida,
        zelda,
        monstros,
        items,
    )

    while True:
        print(masmorra)
        if not masmorra.passo():
            print(masmorra)
            break


# Fim Main

# Início Classes


class ObjetoRenderizavelNaMatiz:
    def __init__(
        self,
        aparencia: str,
        posicao: tuple[int, ...],
    ) -> None:
        self._aparencia = aparencia
        self._posicao = posicao

    @property
    def posicao(self) -> tuple[int, ...]:
        """
        Retorna o atribuo posicao
        """
        return self._posicao

    def __str__(self) -> str:
        """
        Retorna o caractere aparencia do objeto
        """
        return self._aparencia

    def passo(self) -> None:
        """
        Executa os passo o objeto
        """
        pass


class Endidade(ObjetoRenderizavelNaMatiz):
    def __init__(
        self,
        aparencia: str,
        posicao: tuple[int, ...],
        vida: int,
        ataque: int,
    ):
        # repassa a aparencia e a posicao para a classe mae
        super().__init__(aparencia, posicao)
        self._vida: int = vida
        self._ataque: int = ataque
        self._limites: tuple[int, ...] = (0, 0)
        self._esta_morto: bool = False
        self._direcoes: dict[str, tuple[int, ...]] = {
            "esquerda": (0, -1),
            "cima": (-1, 0),
            "direita": (0, 1),
            "baixo": (1, 0),
        }

    def tomar_dano(self, valor: int) -> int:
        """
        Efetua efeito do ataque na Entidade, caso chege a 0
        muda o atribuo self._esta_morto para True
        retorna o dano causado no mostro, que no máximo
        é iqual a sua vida
        """
        if self._vida - valor <= 0:
            self._esta_morto = True
            valor = self.vida
            self._aparencia = "X"
        self._vida -= valor
        return valor

    def _mover_str(self, strdirecao: str) -> None:
        """
        Executa a função mover de acordo com uma string
        informando a direcao por escrito
        ( direções definidas no atributo _direcoes)
        """
        self._mover(self._direcoes.get(strdirecao, (0, 0)))

    def _mover(self, direcao: tuple[int, ...]) -> None:
        """
        Muda a posição do objeto, dentro dos limites da matriz
        """
        pos_mover_linha, pos_mover_coluna = tuple(
            posicao + direcao
            for posicao, direcao in zip(self._posicao, direcao)
        )
        limites_linha, limites_coluna = self._limites
        if not (0 <= pos_mover_linha < limites_linha) or not (
            0 <= pos_mover_coluna < limites_coluna
        ):
            return
        self._posicao = (pos_mover_linha, pos_mover_coluna)

    @property
    def ataque(self) -> int:
        """
        Retorna o atribuo ataque
        """
        return self._ataque

    @property
    def esta_morto(self) -> bool:
        """
        Retorna o atribuo esta_morto
        """
        return self._esta_morto

    @property
    def vida(self) -> int:
        """
        Retorna o atribuo vida
        """
        return self._vida

    @property
    def limites(self) -> tuple[int, ...]:
        """
        Retorna o atribuo limite
        """
        return self._limites

    @limites.setter
    def limites(self, novo_limite: tuple[int, ...]) -> None:
        """
        Seta o atribuo limite
        """
        self._limites = novo_limite


class Zelda(Endidade):
    def __init__(
        self,
        aparencia: str,
        posicao: tuple[int, ...],
        vida: int,
        ataque: int,
    ):
        super().__init__(aparencia, posicao, vida, ataque)
        self._efeitos_da_maldicao: dict[str, Callable[[], None]] = {
            "mover até última linha": self._mover_ate_ultima_linha,
            "mover de acordo com a linha": self._mover_de_acordo_com_a_linha,
        }
        self._efeito_da_maldicao: str = "mover até última linha"

    def passo(self) -> None:
        """
        Executa o efeito da maldição que determina a movimentação
        do personagem
        """
        self._efeitos_da_maldicao[self._efeito_da_maldicao]()

    def somar_vida(self, valor: int) -> None:
        """
        soma um valor a vida do personagem, caso seja menor
        que 1, o valor absoluto é repassado a função tomar_dano
        """
        if valor < 0:
            self.tomar_dano(-valor)
            return
        self._vida += valor

    def somar_ataque(self, valor: int) -> None:
        """
        Soma valor ao atribuo ataque
        caso o valor deixe o o valor do ataque
        menor que 1, o define o valor do ataque como 1
        """
        if self._ataque + valor < 1:
            self._ataque = 1
            return
        self._ataque += valor

    def _mudar_efeito_maldicao(self, novo_efeito: str) -> None:
        """
        Muda o efeito da maldição do personagem e executa
        o um novo passo
        """
        self._efeito_da_maldicao = novo_efeito
        self.passo()

    def _mover_ate_ultima_linha(self) -> None:
        """
        Define o comportamento da maldição de mover
        o personagem até a ultima linha
        """
        pos_linha, _ = self._posicao
        limite_linha, _ = self._limites
        if pos_linha + 1 < limite_linha:
            self._mover_str("baixo")
        else:
            self._mudar_efeito_maldicao("mover de acordo com a linha")

    def _mover_de_acordo_com_a_linha(self) -> None:
        """
        Define a direção que o personagem vai se
        mover de acordo com a linha
        """
        pos_linha, pos_coluna = self._posicao
        _, limite_coluna = self._limites
        eh_linha_par: bool = pos_linha % 2 == 0
        if eh_linha_par and 0 <= (pos_coluna - 1):
            self._mover_str("esquerda")
        elif not (eh_linha_par) and (pos_coluna + 1) < limite_coluna:
            self._mover_str("direita")
        elif pos_linha > 0:
            self._mover_str("cima")


class Monstro(Endidade):
    def __init__(
        self,
        tipo: str,
        posicao: tuple[int, ...],
        vida: int,
        ataque: int,
    ):
        super().__init__(tipo, posicao, vida, ataque)
        self._tipos: dict[str, tuple[int, ...]] = {
            "U": self._direcoes["cima"],
            "D": self._direcoes["baixo"],
            "L": self._direcoes["esquerda"],
            "R": self._direcoes["direita"],
        }
        self._vetor_comportamento = self._tipos[tipo]

    def passo(self) -> None:
        """
        Executa o comportamento do Monstro
        """
        self._mover(self._vetor_comportamento)


class Item(ObjetoRenderizavelNaMatiz):
    def __init__(
        self,
        tipo: str,
        posicao: tuple[int, ...],
        nome: str,
        status: int,
    ) -> None:
        super().__init__(tipo, posicao)
        self._nome: str = nome
        self._tipo: str = tipo
        self._status: int = status

    @property
    def tipo(self) -> str:
        """
        Retorna o atribuo tipo
        """
        return self._tipo

    @property
    def status(self) -> int:
        """
        Retorna o atribuo status
        """
        return self._status

    @property
    def nome(self) -> str:
        """
        Retorna o atribuo nome
        """
        return self._nome


class SaidaMasmorra(ObjetoRenderizavelNaMatiz):
    def __init__(self, aparencia: str, posicao: tuple[int, ...]) -> None:
        super().__init__(aparencia, posicao)
        self._zelda_saiu = False

    @property
    def zelda_saiu(self) -> bool:
        """
        Retorna o atribuo personagem_saiu
        """
        return self._zelda_saiu

    @zelda_saiu.setter
    def zelda_saiu(self, value: bool) -> None:
        """
        Seta o atribuo personagem_saiu
        """
        self._zelda_saiu = value


class Masmorra:
    def __init__(
        self,
        dimensoes: tuple[int, ...],
        saida: SaidaMasmorra,
        zelda: Zelda,
        lista_de_monstros: list[Monstro],
        lista_de_items: list[Item],
    ) -> None:
        self._dimensoes = dimensoes
        self._saida: SaidaMasmorra = saida
        self._zelda = zelda
        self._monstros: list[Monstro] = lista_de_monstros
        self._items: list[Item] = lista_de_items
        self._terminou = False
        self._interacoes: dict[type, Callable[[Any], None]] = {
            Monstro: self._interacao_monstro,
            Item: self._interacao_item,
            SaidaMasmorra: self._interacao_saida_masmorra,
        }
        for entidade in [self._zelda] + self._monstros:
            entidade.limites = dimensoes

    def passo(self) -> bool:
        for objeto in (
            [self._zelda] + [self._saida] + self._items + self._monstros
        ):
            objeto.passo()
            if (
                objeto.posicao == self._zelda.posicao
                and id(objeto) != id(self._zelda)
                and not self._zelda.esta_morto
                and not self._saida.zelda_saiu
            ):
                self._interacoes[type(objeto)](objeto)
                if self._zelda.esta_morto:
                    self._terminou = True
        return not self._terminou

    def _interacao_monstro(self, monstro: Monstro) -> None:
        dano = monstro.tomar_dano(self._zelda.ataque)
        print(
            "O Personagem deu",
            dano,
            "de dano ao monstro na posicao",
            self._zelda.posicao,
        )
        if monstro.esta_morto:
            self._monstros.remove(monstro)
            return
        dano = self._zelda.tomar_dano(monstro.ataque)
        print(
            "O Monstro deu",
            dano,
            "de dano ao Personagem. Vida restante =",
            self._zelda.vida,
        )

    def _interacao_item(self, item: Item) -> None:
        interacoes: dict[str, Callable[[int], None]] = {
            "v": self._zelda.somar_vida,
            "d": self._zelda.somar_ataque,
        }
        interacoes[item.tipo](item.status)
        print(
            "[",
            item.tipo,
            "]Personagem adquiriu o objeto ",
            item.nome,
            " com status de ",
            item.status,
            sep="",
        )
        self._items.remove(item)

    def _interacao_saida_masmorra(self, saida: SaidaMasmorra) -> None:
        saida.zelda_saiu = True
        self._terminou = True

    def __str__(self) -> str:
        # gera o plano de fundo da matriz
        linhas, colunas = self._dimensoes
        matriz: list[list[str]] = [
            ["." for _ in range(colunas)] for _ in range(linhas)
        ]
        # coloca os objetos na matrix
        for objeto in (
            self._items + self._monstros + [self._saida] + [self._zelda]
        ):
            linha, coluna = objeto.posicao
            matriz[linha][coluna] = str(objeto)
        # Retorna a matriz
        return (
            "\n".join([" ".join(linha) for linha in matriz])
            + "\n"
            + ("\nChegou ao fim!" if self._saida.zelda_saiu else "")
        )


# Fim Classes

main() if __name__ == "__main__" else None
