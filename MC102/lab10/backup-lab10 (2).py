from typing import Any


# Início Main
def main() -> None:
    aloy = Aloy()
    numero_de_maquinas = int(input())
    numero_combate: int = 0
    while (
        numero_de_maquinas > 0
        and not aloy.esta_morto
        and not aloy.esta_sem_flechas
    ):
        numero_de_maquinas_no_combate = int(input())
        numero_de_maquinas -= numero_de_maquinas_no_combate
        maquinas_no_combate = [
            Maquina() for _ in range(numero_de_maquinas_no_combate)
        ]
        combate: Combate = Combate(numero_combate, aloy, maquinas_no_combate)
        combate.iniciar()
        print(combate.resultado, end="")
        aloy.recolher_flecas()
        aloy.descanso_graciosso()
        numero_combate += 1

    if not aloy.esta_morto and not aloy.esta_sem_flechas:
        print("Aloy provou seu valor e voltou para sua tribo.")
    elif aloy.esta_sem_flechas:
        print("Aloy ficou sem flechas e recomeçará sua missão mais preparada.")
    else:
        print("Aloy foi derrotada em combate e não retornará a tribo.")


# Fim Main


def ziplista(lista: list[Any]) -> Any:
    return zip(lista[::2], lista[1::2])


# Início Classes


class Entidade:
    def __init__(self, vida: int):
        self._vida = vida
        self._esta_morto = False
        self._esta_sem_flechas = False

    def tomar_dano(self, valor: int) -> None:
        if self._vida - valor <= 0:
            self._vida = 0
            self._esta_morto = True
        else:
            self._vida -= valor

    @property
    def esta_morto(self) -> bool:
        return self._esta_morto

    @property
    def vida(self) -> int:
        return self._vida


class Aloy(Entidade):
    def __init__(self) -> None:
        super().__init__(int(input()))
        self._vida_maxima: int = self._vida
        self._flechas: dict[str, list[int]] = {
            tipo: [int(quantidade), int(quantidade)]
            for tipo, quantidade in ziplista(input().split())
        }

    @property
    def flechas(self) -> dict[str, list[int]]:
        return self._flechas

    @property
    def esta_sem_flechas(self) -> bool:
        return self._esta_sem_flechas

    def atirar_fleca(self, flecha: str) -> None:
        self._flechas[flecha][0] -= 1
        if not [True for quant, _ in self._flechas.values() if quant != 0]:
            self._esta_sem_flechas = True

    def descanso_graciosso(self) -> None:
        if self._vida_maxima // 2 > self._vida:
            self._vida += self._vida_maxima // 2
        else:
            self._vida = self._vida_maxima

    def recolher_flecas(self) -> None:
        for flecha, (_, quantidade_max) in self._flechas.items():
            self._flechas[flecha][0] = quantidade_max

    # @vida.setter
    # def vida(self, vida: int) -> None:
    #     self._vida = vida


class Maquina(Entidade):
    def __init__(self) -> None:
        (
            vida,
            pontos_de_ataque,
            quant_partes,
        ) = input().split()
        super().__init__(int(vida))
        self._pontos_de_ataque: int = int(pontos_de_ataque)
        self._fraquezas: dict[str, tuple[str, int, tuple[int, int]]] = {}
        for _ in range(int(quant_partes)):
            parte, fraqueza, dano_max, coord_x, coord_y = input().split(", ")
            self._fraquezas[parte] = (
                fraqueza,
                int(dano_max),
                (int(coord_x), int(coord_y)),
            )

    @property
    def pontos_de_ataque(self) -> int:
        return self._pontos_de_ataque

    @property
    def fraquezas(self) -> dict[str, tuple[str, int, tuple[int, int]]]:
        return self._fraquezas


class Combate:
    def __init__(
        self, ncombate: int, aloy: Aloy, maquinas_no_combate: list[Maquina]
    ) -> None:
        self._ncombate: int = ncombate
        self._guerreira: Aloy = aloy
        self._lista_maquinas: list[Maquina] = maquinas_no_combate
        self._emcombate: bool = True
        self._texto: str = ""
        self._criticos: dict[tuple[int, tuple[int, int]], int] = dict()

    def iniciar(self) -> None:
        self._texto += (
            "Combate "
            + str(self._ncombate)
            + ", vida = "
            + str(self._guerreira.vida)
            + "\n"
        )
        while self._emcombate:
            self._round()

    def _critico(self, indice_alvo: int, posicao: tuple[int, int]) -> None:
        chave = (indice_alvo, posicao)
        if not (chave in self._criticos):
            self._criticos[chave] = 1
            return
        self._criticos[chave] += 1

    def _round(self) -> None:
        for _ in range(3):
            (
                indice_alvo,
                parte,
                tipo_flecha,
                coord_x,
                coord_y,
            ) = input().split(", ")

            self._guerreira.atirar_fleca(tipo_flecha)

            alvo = self._lista_maquinas[int(indice_alvo)]

            parte_alvo: tuple[str, int, tuple[int, int]] = alvo.fraquezas[
                parte
            ]

            fraqueza_parte, dano_max, coordenada_fraqueza = parte_alvo
            dano = self.calcular_dano(
                dano_max,
                coordenada_fraqueza,
                (int(coord_x), int(coord_y)),
            )
            # print(
            #     (
            #         fraqueza_parte != tipo_flecha
            #         and not (fraqueza_parte == "todas")
            #     )
            #     or fraqueza_parte == "nemhuma"
            # )
            if int(dano_max) == int(dano):
                # print("critical")
                self._critico(int(indice_alvo), coordenada_fraqueza)
                # print(" - " + indice_alvo + ", " + str(coordenada_fraqueza))
            if fraqueza_parte == "nenhuma" or (
                fraqueza_parte != tipo_flecha and fraqueza_parte != "todas"
            ):
                dano //= 2
            # print(int(dano_max), int(dano))
            # print(int(dano_max) == int(dano))
            alvo.tomar_dano(dano)
            if alvo.esta_morto:
                self._texto += "Máquina " + indice_alvo + " derrotada\n"
                # Verifca se todas as maquinas morreram
                if not [
                    True
                    for maquina in self._lista_maquinas
                    if not maquina.esta_morto
                ]:
                    self._emcombate = False
                    return
        self._guerreira.tomar_dano(
            sum(
                [
                    maquina.pontos_de_ataque
                    for maquina in self._lista_maquinas
                    if not maquina.esta_morto
                ]
            )
        )
        if self._guerreira.esta_sem_flechas:
            self._emcombate = False
            return
        # print(
        #     sum(
        #         [
        #             maquina.pontos_de_ataque
        #             for maquina in self._lista_maquinas
        #             if not maquina.esta_morto
        #         ]
        #     )
        # )
        if self._guerreira.esta_morto:
            self._emcombate = False

    def calcular_dano(
        self,
        dano_max: int,
        dano_max_coord: tuple[int, int],
        coord: tuple[int, int],
    ) -> int:
        # print(
        #     dano_max,
        #     dano_max_coord,
        #     coord,
        # )
        # print(
        #     dano_max
        #     - (
        #         abs(dano_max_coord[0] - coord[0])
        #         + abs(dano_max_coord[0] - coord[1])
        #     )
        # )
        dano = dano_max - (
            abs(dano_max_coord[0] - coord[0])
            + abs(dano_max_coord[1] - coord[1])
        )

        return dano if dano > 0 else 0

    @property
    def resultado(self) -> str:
        self._texto += (
            "Vida após o combate = " + str(self._guerreira.vida) + "\n"
        )
        if (
            not self._guerreira.esta_morto
            and not self._guerreira.esta_sem_flechas
        ):
            flecas_usadas: dict[str, str] = {
                tipo_flecha: str(quant_max - quant) + "/" + str(quant_max)
                for tipo_flecha, (
                    quant,
                    quant_max,
                ) in self._guerreira.flechas.items()
                if quant != quant_max
            }
            self._texto += "Flechas utilizadas:\n"
            for tipo_flecha, uso in flecas_usadas.items():
                self._texto += "- " + str(tipo_flecha) + ": " + uso + "\n"

        maquinas_critico: list[int] = list(
            set([indice_maquina for indice_maquina, _ in self._criticos])
        )
        # print(maquinas_critico)

        if maquinas_critico:
            self._texto += "Críticos acertados:\n"

        for indice_maquina in maquinas_critico:
            self._texto += (
                "Máquina "
                + str(indice_maquina)
                + ":\n"
                + "".join(
                    [
                        "- ("
                        + str(coord_x)
                        + ", "
                        + str(coord_y)
                        + "): "
                        + str(quant)
                        + "x"
                        + "\n"
                        for (
                            _indice_maquina,
                            (coord_x, coord_y),
                        ), quant in self._criticos.items()
                        if _indice_maquina == indice_maquina
                    ]
                )
            )
        # if not self._guerreira.esta_morta:
        #     self._texto += "Aloy provou seu valor e voltou para sua tribo."
        return self._texto


class Log:
    def __init__(self) -> None:
        pass


main() if __name__ == "__main__" else None
# Fim Classes
