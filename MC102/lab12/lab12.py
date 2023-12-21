from typing import Any


def main() -> None:
    jogadores: list[Jogador] = [
        Jogador(str(i), Cartas(Carta(carta) for carta in input().split(", ")))
        for i in range(1, int(input()) + 1)
    ]
    numero_antes_de_blefes = int(input())
    jogo: Jogo = Jogo(jogadores, numero_antes_de_blefes)
    jogo.iniciar()


class Carta:
    def __init__(self, carta_string: str) -> None:
        self._aparencia = carta_string
        self._numero: int = self._simbolo_numero_para_inteiro(carta_string)
        self._naipe: int = self._simbolo_naipe_para_inteiro(carta_string)

    @property
    def numero(self) -> str:
        """
        Retorna o numero da carta em str
        """
        return self._aparencia[:-1]

    @property
    def naipe(self) -> str:
        """
        Retorna o naipe da carta em str
        """
        return self._aparencia[-1]

    @staticmethod
    def _simbolo_numero_para_inteiro(carta_string: str) -> int:
        """
        Retorna um inteiro de acordo com a ordem de poder
        da da carta_string
        """
        simbolo_numero = carta_string[:-1]
        return (
            int(simbolo_numero)
            if simbolo_numero.isnumeric()
            else {
                letra: numero
                for letra, numero in zip(
                    ["A", "J", "Q", "K"], [1] + list(range(11, 14))
                )
            }[simbolo_numero]
        )

    @staticmethod
    def _simbolo_naipe_para_inteiro(carta_string: str) -> int:
        """
        Retorna um inteiro de acordo com a ordem de poder
        da carta_string
        """
        simbolo_naipe = carta_string[-1]
        return {ch: i for ch, i in zip(["O", "E", "C", "P"], range(1, 5))}[
            simbolo_naipe
        ]

    def sucessora(self) -> "Carta":
        """
        Retorna a carta sucessora da carta atual em ordem de poder
        sem considerar o naipe
        """
        carta = Carta(self._aparencia)
        carta._numero += 1
        carta._naipe = 0
        return carta

    def antecessora(self) -> "Carta":
        """
        Retorna a carta antecessora da carta atual em ordem de poder
        sem considerar o naipe
        """
        carta = Carta(self._aparencia)
        carta._numero -= 1
        carta._naipe = 0
        return carta

    def atual(self) -> "Carta":
        """
        Retorna a carta atual com naipe nulo
        """
        carta = Carta(self._aparencia)
        carta._naipe = 0
        return carta

    def __eq__(self, outra: Any) -> bool:
        """
        Compara se a carta atual e a outra mesma em orderm de poder
        """
        return (self._numero, self._naipe) == (outra._numero, outra._naipe)

    def __ne__(self, outra: Any) -> bool:
        """
        Compara se a carta atual e a outra sao mesmas em ordem de poder
        """
        return (self._numero, self._naipe) != (outra._numero, outra._naipe)

    def __gt__(self, outra: "Carta") -> bool:
        """
        Compara se a carta atual e maior que a outra em ordem de poder
        """
        return (self._numero, self._naipe) > (outra._numero, outra._naipe)

    def __lt__(self, outra: "Carta") -> bool:
        """
        Compara se a carta atual e menor que a outra em ordem de poder
        """
        return (self._numero, self._naipe) < (outra._numero, outra._naipe)

    def __ge__(self, outra: "Carta") -> bool:
        """
        Compara se a carta atual e maior ou igual outra em ordem de poder
        """
        return (self._numero, self._naipe) >= (outra._numero, outra._naipe)

    def __le__(self, outra: "Carta") -> bool:
        """
        Compara se a carta atual e menor ou igual a a carta atual
        """
        return (self._numero, self._naipe) <= (outra._numero, outra._naipe)

    def __str__(self) -> str:
        """
        Retorna a aparencia da carta em simbolo
        """
        return self._aparencia


class Cartas(list[Carta]):
    def indice(self, valor: Carta, inicio: int = 0, fim: int = None) -> int:
        """
        retorna o indice de onde um valor está ou estaria na lista
        """
        fim = fim if fim is not None else len(self) - 1
        # Busca binária recursiva
        if inicio > fim:
            return inicio
        else:
            meio = (inicio + fim) // 2
            if self[meio] < valor:
                return self.indice(valor, inicio, meio - 1)
            else:
                return self.indice(valor, meio + 1, fim)

    def inserir(
        self, carta: Carta, inicio: int = 0, final: int = None
    ) -> None:
        """
        Inseri uma carta na lista
        """
        final = final if final is not None else len(self) - 1
        indice = self.indice(carta, inicio, final)
        self[indice:indice] = [carta]

    def receber(self, cartas: "Cartas") -> None:
        """
        Inseri uma colecao de cartas de forma ordernada na lista
        """
        for carta in cartas:
            self.inserir(carta)

    def organizar(
        self, indice_inicial: int = 0, indice_final: int = 1
    ) -> None:
        """
        Organiza as cartas de forma descresente
        """
        if indice_final >= len(self):
            return
        else:
            self.inserir(
                self.separar_cartas(indice_final, indice_final + 1)[0],
                indice_inicial,
                indice_final - 1,
            )
            self.organizar(indice_inicial, indice_final + 1)

    def separar_cartas(
        self, indice_inicial: int, indice_final: int
    ) -> "Cartas":
        """
        Remove das lista de cartas uma colecão de cartas
        determinadas pelos parâmetros indice_inicial e indice_final
        e retorna as cartas removidas
        """
        cartas_separadas = self[indice_inicial:indice_final]
        self[indice_inicial:indice_final] = []
        return Cartas(cartas_separadas)

    def separar_cartas_com_base_referencia(
        self, carta_referencia: Carta
    ) -> "Cartas":
        """
        Remove uma colecao de cartas de mesmo numero imediatamente
        maiores ou iquais a a carta_de_referencia e
        retorna a lista removida
        """
        indice_final = self.indice(carta_referencia)
        indice_inicial = self.indice(self[indice_final - 1].sucessora())
        return self.separar_cartas(indice_inicial, indice_final)

    def separar_todas(self) -> "Cartas":
        """
        Remove todas as cartas e retorna as cartas
        que foram removidas
        """
        return self.separar_cartas(0, len(self))

    def __str__(self) -> str:
        """
        Exibe a lista de cartas separadas por espaço
        """
        return (" " + " ".join([str(carta) for carta in self])) if self else ""


class Jogador:
    def __init__(self, nome: str, mao: Cartas) -> None:
        self.nome: str = nome
        self.mao: Cartas = mao
        self.mao.organizar()

    def jogar(
        self, carta_de_referencia: Carta, pilha_de_descarte: Cartas
    ) -> tuple[str, int]:
        """
        Emplementa a jodada de  um jogador, com base a carta_ref
        retorna o numero da carta que jogou e a quantidade de cartas
        """
        # Procura na mão cartas de numer maior o igual a carta_referencia
        cartas_jogaveis = self.mao.separar_cartas_com_base_referencia(
            carta_de_referencia
        )
        # Verifica se há cartas
        if not cartas_jogaveis:
            # Não tem cartas, blefando...
            cartas_jogaveis = self.mao.separar_cartas_com_base_referencia(
                Carta(self.mao[-1].numero + "O")
            )
            numero_das_cartas = carta_de_referencia.numero
        else:
            # Tem cartas
            numero_das_cartas = cartas_jogaveis[0].numero

        # Joga as cartas na pilha de descarte
        pilha_de_descarte.extend(cartas_jogaveis[::-1])
        return (
            numero_das_cartas,
            len(cartas_jogaveis),
        )

    def __str__(self) -> str:
        return self.nome


class Jogo:
    def __init__(
        self, jogadores: list[Jogador], numero_antes_de_blefes: int
    ) -> None:
        self._jogadores: list[Jogador] = jogadores
        self._pilha_de_descarte: Cartas = Cartas()
        self._numero_antes_do_duvido = numero_antes_de_blefes
        self._contador_para_duvido = 0
        print(self)

    @staticmethod
    def item_e_proximo_item(lista: list[Any]) -> list[tuple[Any, ...]]:
        """
        Retorna uma lista de tuplas com o item e o próximo
        """
        return [
            tuple((lista[i], lista[(i + 1) % len(lista)]))
            for i in range(len(lista))
        ]

    def _eh_round_duvido(self) -> bool:
        """
        Conta e retorna se o round tem um duvido
        """
        self._contador_para_duvido += 1
        if self._contador_para_duvido == self._numero_antes_do_duvido:
            self._contador_para_duvido = 0
            return True
        return False

    def _round_duvido(
        self,
        jogador_atual: Jogador,
        jogador_duvidador: Jogador,
        numero_das_cartas: str,
        quantidade_de_cartas: int,
    ) -> None:
        """
        Executa os acontecimentos de um duvido
        """
        # Printa o jogador que duvidou
        print("Jogador " + jogador_duvidador.nome + " duvidou.")

        # Testa se o jogadore_atual estava blefando
        jogador_perdeu_o_duvido = jogador_duvidador
        if not all(
            carta.numero == numero_das_cartas
            for carta in self._pilha_de_descarte[-quantidade_de_cartas:]
        ):
            jogador_perdeu_o_duvido = jogador_atual
        jogador_perdeu_o_duvido.mao.receber(
            self._pilha_de_descarte.separar_todas()
        )

        # Printa o jogo
        print(self)

    def _mostrar_jogada(
        self,
        jogador: Jogador,
        quantidade_de_cartas: int,
        simbolo_numero_das_cartas: int,
    ) -> None:
        """
        Imprime a jodada de um jogador
        """
        print(
            "[Jogador "
            + str(jogador)
            + "] "
            + str(quantidade_de_cartas)
            + " carta(s) "
            + str(simbolo_numero_das_cartas)
            + "\nPilha:"
            + str(self._pilha_de_descarte)
        )

    def iniciar(self) -> None:
        """
        Inicia o jogo e executas rodadas até achar um ganhador
        """
        carta_de_referencia = Carta("AO")
        acabou = False
        while not acabou:
            # Rodada
            for jogador_atual, jogador_proximo in self.item_e_proximo_item(
                self._jogadores
            ):
                # Jogada do jogadore_atual
                (
                    simbolo_numero_das_cartas,
                    quantidade_de_cartas_da_jogada,
                ) = jogador_atual.jogar(
                    carta_de_referencia, self._pilha_de_descarte
                )

                # Mostrar a jogada
                self._mostrar_jogada(
                    jogador_atual,
                    quantidade_de_cartas_da_jogada,
                    simbolo_numero_das_cartas,
                )

                # Verifica se é um round com duvido
                if self._eh_round_duvido():
                    self._round_duvido(
                        jogador_atual,
                        jogador_proximo,
                        simbolo_numero_das_cartas,
                        quantidade_de_cartas_da_jogada,
                    )
                    # Reinicia a carta de carta_de_referencia
                    carta_de_referencia = Carta("AO")

                else:
                    # Seta a carta de carta_de_referencia
                    # para o valor da jogadoa atuaal
                    carta_de_referencia = Carta(
                        simbolo_numero_das_cartas + "O"
                    )

                # Verifica se o jogador atual ganhador
                if not jogador_atual.mao:
                    print("Jogador " + str(jogador_atual) + " é o vencedor!")
                    acabou = True
                    break

    def __str__(self) -> str:
        """
        Retorna uma string do jogo completo
        """
        return "\n".join(
            [
                "Jogador " + jogador.nome + "\nMão:" + str(jogador.mao)
                for jogador in self._jogadores
            ]
            + ["Pilha:" + str(self._pilha_de_descarte)]
        )


main() if __name__ == "__main__" else None
