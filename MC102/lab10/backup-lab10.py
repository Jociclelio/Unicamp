# Início Main
from typing import Any, Callable, Iterable
from math import floor


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

        maquinas_no_combate = Maquinas(
            Maquina() for _ in range(numero_de_maquinas_no_combate)
        )
        # maquinas_no_combate = Maquinas(numero_de_maquinas_no_combate)
        combate: Combate = Combate(numero_combate, aloy, maquinas_no_combate)

        print(combate, end="")

        aloy.recolher_flecas()
        aloy.recuperar_vida()

        numero_combate += 1

    if not aloy.esta_morto and not aloy.esta_sem_flechas:
        print("Aloy provou seu valor e voltou para sua tribo.")
    elif aloy.esta_sem_flechas:
        print("Aloy ficou sem flechas e recomeçará sua missão mais preparada.")
    else:
        print("Aloy foi derrotada em combate e não retornará a tribo.")


# Fim Main


def ziplista_por_pares(
    lista: list[str],
) -> list[tuple[str, int]]:
    """
    retorna um zip com os indices agrupados em pares

    """
    return list(zip(map(str, lista[::2]), map(int, lista[1::2])))


# Início Classes


class Entidade:
    def __init__(self, vida: int):
        self._vida = vida
        self._esta_morto = False

    def tomar_dano(self, valor: int) -> None:
        """
        efetua efeito do dano na Entidade, caso chege a 0
        muda o atribuo self._esta_morto para 0
        """
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
            for tipo, quantidade in ziplista_por_pares(input().split())
        }
        self._esta_sem_flechas = False

    @property
    def flechas(self) -> dict[str, list[int]]:
        return self._flechas

    @property
    def esta_sem_flechas(self) -> bool:
        return self._esta_sem_flechas

    def atirar_flecha(self, flecha: str) -> None:
        self._flechas[flecha][0] -= 1
        if all(quant == 0 for quant, _ in self._flechas.values()):
            self._esta_sem_flechas = True

    def recuperar_vida(self) -> None:
        if floor(0.5 * self._vida_maxima) > self._vida:
            self._vida += floor(0.5 * self._vida_maxima)
        else:
            self._vida = self._vida_maxima

    def recolher_flecas(self) -> None:
        for flecha, (_, quantidade_max) in self._flechas.items():
            self._flechas[flecha][0] = quantidade_max

    def __str__(self) -> str:
        texto = ""
        if not self.esta_morto and not self.esta_sem_flechas:
            flecas_usadas: dict[str, str] = {
                tipo_flecha: str(quant_max - quant) + "/" + str(quant_max)
                for tipo_flecha, (
                    quant,
                    quant_max,
                ) in self.flechas.items()
                if quant != quant_max
            }
            texto += "Flechas utilizadas:\n"
            for tipo_flecha, uso in flecas_usadas.items():
                texto += "- " + str(tipo_flecha) + ": " + uso + "\n"
        return texto


class Parte_maquina:
    def __init__(
        self, fraqueza: str, dano_max: int, coordenada: tuple[int, int]
    ) -> None:
        self._fraqueza: str = fraqueza
        self._dano_max: int = dano_max
        self._coordenada: tuple[int, int] = coordenada
        self._numero_acertos_criticos: int = 0
        self._index: int = 0
        self._atributos: list[
            str | int | tuple[int, int] | Callable[[], None]
        ] = [
            self._fraqueza,
            self._dano_max,
            self._coordenada,
            self._numero_acertos_criticos,
        ]

    @property
    def tem_critico(self) -> bool:
        return self._numero_acertos_criticos > 0

    def somar_critico(self) -> None:
        self._numero_acertos_criticos += 1

    def __iter__(self) -> Any:
        return iter(self._atributos)

    def __next__(self) -> Any:
        if self._index >= len(self._atributos):
            raise StopIteration
        item = self._atributos[self._index]
        self._index += 1
        return item

    def __str__(self) -> str:
        coord_x, coord_y = self._coordenada
        return (
            "- ("
            + str(coord_x)
            + ", "
            + str(coord_y)
            + "): "
            + str(self._numero_acertos_criticos)
            + "x"
            + "\n"
        )


class Maquina(Entidade):
    def __init__(self) -> None:
        (
            vida,
            pontos_de_ataque,
            quant_partes,
        ) = input().split()
        super().__init__(int(vida))
        self._pontos_de_ataque: int = int(pontos_de_ataque)
        self._fraquezas: dict[str, Parte_maquina] = {
            parte: Parte_maquina(
                fraqueza, int(dano_max), (int(coord_x), int(coord_y))
            )
            for parte, fraqueza, dano_max, coord_x, coord_y in [
                input().split(", ") for _ in range(int(quant_partes))
            ]
        }

    @property
    def pontos_de_ataque(self) -> int:
        return self._pontos_de_ataque

    @property
    def fraquezas(self) -> dict[str, Parte_maquina]:
        return self._fraquezas

    def __str__(self) -> str:
        return "".join(
            [
                str(parte)
                for parte in self._fraquezas.values()
                if parte.tem_critico
            ]
        )


class Maquinas(list[Maquina]):
    def __str__(self) -> str:
        texto = ""
        if not all(str(maquina) == "" for maquina in self):
            texto += "Críticos acertados:\n"
            for i in range(len(self)):
                if str(self[i]):
                    texto += "Máquina " + str(i) + ":" + "\n"
                    texto += str(self[i])
        return texto


class Combate:
    def __init__(
        self,
        numero_combate: int,
        aloy: Aloy,
        maquinas_no_combate: Maquinas,
    ) -> None:
        self._numero_combate: int = numero_combate
        self._guerreira: Aloy = aloy
        self._maquinas: Maquinas = maquinas_no_combate
        self._emcombate: bool = True
        self._texto: str = (
            "Combate "
            + str(self._numero_combate)
            + ", vida = "
            + str(self._guerreira.vida)
            + "\n"
        )
        self._iniciar()

    def _iniciar(self) -> None:
        while self._emcombate:
            self._round()

    def _round(self) -> None:
        for _ in range(3):
            self._turno_aloy()
            if not self._emcombate:
                return
        self._turno_maquinas()

    def _turno_aloy(self) -> None:
        (
            indice_alvo,
            parte,
            tipo_flecha,
            coord_x,
            coord_y,
        ) = input().split(", ")
        self._guerreira.atirar_flecha(tipo_flecha)

        alvo = self._maquinas[int(indice_alvo)]

        parte_alvo: Parte_maquina = alvo.fraquezas[parte]

        (
            fraqueza_parte,
            dano_max,
            coordenada_fraqueza,
            _,
        ) = parte_alvo
        dano = self._calcular_dano(
            dano_max,
            coordenada_fraqueza,
            (int(coord_x), int(coord_y)),
        )
        if int(dano_max) == int(dano):
            parte_alvo.somar_critico()
            # print(alvo.fraquezas[parte]._numero_acertos_criticos)
        if fraqueza_parte == "nenhuma" or (
            fraqueza_parte != tipo_flecha and fraqueza_parte != "todas"
        ):
            dano //= 2
        alvo.tomar_dano(dano)
        if alvo.esta_morto:
            self._texto += "Máquina " + indice_alvo + " derrotada\n"
            if not [
                True for maquina in self._maquinas if not maquina.esta_morto
            ]:
                self._emcombate = False

    def _turno_maquinas(self) -> None:
        self._guerreira.tomar_dano(
            sum(
                [
                    maquina.pontos_de_ataque
                    for maquina in self._maquinas
                    if not maquina.esta_morto
                ]
            )
        )
        if self._guerreira.esta_sem_flechas or self._guerreira.esta_morto:
            self._emcombate = False

    def _calcular_dano(
        self,
        dano_max: int,
        dano_max_coord: tuple[int, int],
        coord: tuple[int, int],
    ) -> int:
        dano = dano_max - (
            abs(dano_max_coord[0] - coord[0])
            + abs(dano_max_coord[1] - coord[1])
        )
        return dano if dano > 0 else 0

    def __str__(self) -> str:
        self._texto += (
            "Vida após o combate = " + str(self._guerreira.vida) + "\n"
        )
        self._texto += str(self._guerreira)
        self._texto += str(self._maquinas)
        return self._texto


main() if __name__ == "__main__" else None
# Fim Classes
