from math import floor
from typing import Any

# Início Main


def main() -> None:
    # Instância o objeto Aloy
    aloy = Aloy(
        int(input()),
        {
            tipo: [int(quantidade), int(quantidade)]
            for tipo, quantidade in agrupar(input().split())
        },
    )

    # Recebe o número total de máquinas
    numero_de_maquinas = int(input())

    # Declara o contador de combate
    numero_combate: int = 0

    while True:
        # Receve o numero de maquinas no combate
        numero_de_maquinas_no_combate = int(input())

        # subtrai do numero de máquinas totais
        numero_de_maquinas -= numero_de_maquinas_no_combate

        # Instãncia a lista de maquinas
        maquinas: Maquinas = Maquinas()
        for _ in range(numero_de_maquinas_no_combate):
            # Recebe a vida, pontos de ataque e
            # quantidade de partes da máquina
            (
                vida,
                pontos_de_ataque,
                n_partes,
            ) = input().split()

            # Cria do dicionário de partes do alvo
            partes: dict[str, Parte_maquina] = {
                parte: Parte_maquina(
                    fraqueza, int(dano_max), (int(coord_x), int(coord_y))
                )
                for parte, fraqueza, dano_max, coord_x, coord_y in [
                    input().split(", ") for _ in range(int(n_partes))
                ]
            }

            # Adiciona a lista de Máquinas
            maquinas.append(Maquina(int(vida), int(pontos_de_ataque), partes))

        # Instância o combate
        combate: Combate = Combate(numero_combate, aloy, maquinas)

        # Inicia o combate
        combate.iniciar()

        # Printa o resultado do combate
        print(combate.resultado())

        # testa se haverá um nova rodada
        # caso não, sai do while
        if (
            numero_de_maquinas > 0
            and not aloy.esta_morto
            and not aloy.esta_sem_flechas
        ):
            # faz aloy recolher suas flechas
            aloy.recolher_flecas()

            # faz aloy descansar para recuperar vida
            aloy.recuperar_vida()

            # incrementa o numero de combate
            numero_combate += 1
        else:
            break

    # printa a mensagem de acordo o o resultado dos combates
    if not aloy.esta_morto and not aloy.esta_sem_flechas:
        print("Aloy provou seu valor e voltou para sua tribo.")
    elif aloy.esta_sem_flechas:
        print("Aloy ficou sem flechas e recomeçará sua missão mais preparada.")
    else:
        print("Aloy foi derrotada em combate e não retornará a tribo.")


# Fim Main


# Início Funções


def agrupar(lista: list[Any], grupo: int = 2) -> list[tuple[Any, ...]]:
    """
    Agrupa items de uma lista em grupos
    retorna uma lista de tuplas com grupos
    """
    assert len(lista) % grupo == 0
    return [tuple(lista[i : i + grupo]) for i in range(0, len(lista), grupo)]


# Fim Funções

# Início Classes


class Entidade:
    def __init__(self, vida: int):
        # Salva o atributo vida
        self._vida: int = vida

        # Cria o atributo esta_morto
        self._esta_morto: bool = False if self._vida > 0 else True

    def tomar_dano(self, valor: int) -> None:
        """
        Efetua efeito do dano na Entidade, caso chege a 0
        muda o atribuo self._esta_morto para True
        """
        if self._vida - valor <= 0:
            self._vida = 0
            self._esta_morto = True
        else:
            self._vida -= valor

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


class Aloy(Entidade):
    def __init__(self, vida: int, flechas: dict[str, list[int]]) -> None:
        # Repassa o atributo vida para classe mãe
        super().__init__(vida)

        # salva a vida máxima como a vida atual
        self._vida_maxima: int = self._vida

        # Monta o dicionário de flechas
        self._flechas: dict[str, list[int]] = flechas

    @property
    def flechas(self) -> dict[str, list[int]]:
        """
        Retorna o dicionário de flechas
        """
        return self._flechas

    @property
    def esta_sem_flechas(self) -> bool:
        """
        Retorna True caso a aloy esteja sem flechas
        """
        return all(quant == 0 for quant, _ in self._flechas.values())

    def usar_flecha(self, flecha: str) -> bool:
        """
        subitrai o número de flechas do tipo repassado em 1
        caso não tenha a flecha ou tenha acabado retorna False
        caso exista a flecha e tenha quantidade disponível retorna True
        """
        if self._flechas.get(flecha, False):
            self._flechas[flecha][0] -= 1
            return True
        return False

    def recuperar_vida(self) -> None:
        """
        Adiciona até metade da vida máxima a vida
        """
        if floor(0.5 * self._vida_maxima) > self._vida:
            self._vida += floor(0.5 * self._vida_maxima)
        else:
            self._vida = self._vida_maxima

    def recolher_flecas(self) -> None:
        """
        Renova o estoque de todas as flechas para valor inicial
        """
        for flecha, (_, quantidade_max) in self._flechas.items():
            self._flechas[flecha][0] = quantidade_max

    def __str__(self) -> str:
        """
        Exibe as flechas que foram usadas
        """
        if not (self.esta_morto or self.esta_sem_flechas):
            return "Flechas utilizadas:\n" + "\n".join(
                [
                    "- "
                    + str(tipo_flecha)
                    + ": "
                    + str(quant_max - quant)
                    + "/"
                    + str(quant_max)
                    for tipo_flecha, (
                        quant,
                        quant_max,
                    ) in self._flechas.items()
                    if quant < quant_max
                ]
            )
        return ""


class Parte_maquina:
    def __init__(
        self, fraqueza: str, dano_max: int, coordenada: tuple[int, int]
    ) -> None:
        # Salva o atribuo fraqueza
        self._fraqueza: str = fraqueza

        # Salva o atribuo dano_max
        self._dano_max: int = dano_max

        # Salva a coordenada da parte
        self._coordenada: tuple[int, int] = coordenada

        # Inica o numero de acertos críticos em 0
        self._numero_acertos_criticos: int = 0

    @property
    def tem_critico(self) -> bool:
        """
        Retorna True caso a parte tenha sido alvo de um acerto crítico
        """
        return self._numero_acertos_criticos > 0

    @property
    def fraqueza(self) -> str:
        """
        Retorna o atribuo _fraqueza
        """
        return self._fraqueza

    @property
    def dano_max(self) -> int:
        """
        Retorna o atributo _dano_max
        """
        return self._dano_max

    @property
    def coordenada(self) -> tuple[int, int]:
        """
        Retorna o atributo _coordenada
        """
        return self._coordenada

    def somar_critico(self) -> None:
        """
        Soma 1 a contagem de críticos
        """
        self._numero_acertos_criticos += 1

    def __str__(self) -> str:
        """
        Retorna a contagem de críticos a peça formatada
        """
        coord_x, coord_y = self._coordenada
        return (
            "- ("
            + str(coord_x)
            + ", "
            + str(coord_y)
            + "): "
            + str(self._numero_acertos_criticos)
            + "x"
        )


class Maquina(Entidade):
    def __init__(
        self,
        vida: int,
        pontos_de_ataque: int,
        fraquezas: dict[str, Parte_maquina],
    ) -> None:
        # Repassa a vida para o __ini__ da classe mãe
        super().__init__(vida)

        # Salva o atribuo _pontos_de_ataque
        self._pontos_de_ataque: int = pontos_de_ataque

        # Salva o atributo _fraquezas
        self._fraquezas: dict[str, Parte_maquina] = fraquezas

    @property
    def pontos_de_ataque(self) -> int:
        """
        Retorna os pontos de ataque da Máquina
        """
        return self._pontos_de_ataque

    @property
    def fraquezas(self) -> dict[str, Parte_maquina]:
        """
        Retorna o dicionário de fraquezas
        """
        return self._fraquezas

    def __str__(self) -> str:
        """
        Retorna a contagem de críticos das partes da Máquina
        """
        return "\n".join(
            [
                str(parte)
                for parte in self._fraquezas.values()
                if parte.tem_critico
            ]
        )


class Maquinas(list[Maquina]):
    @property
    def estao_todas_mortas(self) -> bool:
        return all(maquina.esta_morto for maquina in self)

    def __str__(self) -> str:
        """
        Retorna os críticos acertados de todas as máquinas
        """
        if not all(str(maquina) == "" for maquina in self):
            return "Críticos acertados:\n" + "\n".join(
                [
                    "Máquina " + str(i) + ":\n" + str(self[i])
                    for i in range(len(self))
                    if str(self[i])
                ]
            )
        return ""


class Combate:
    def __init__(
        self,
        numero_combate: int,
        aloy: Aloy,
        maquinas_no_combate: Maquinas,
    ) -> None:
        # Salva o atributo _numero_combate
        self._numero_combate: int = numero_combate

        # Salva o atributo _guerreira
        self._guerreira: Aloy = aloy

        # Salva a lista de máquinas
        self._maquinas: Maquinas = maquinas_no_combate

        # Salva o primeiro registro do combate
        self._resgistro_do_combate: list[str] = [
            "Combate "
            + str(self._numero_combate)
            + ", vida = "
            + str(self._guerreira.vida)
        ]

    def iniciar(self) -> None:
        """
        Inicia o combate e executa rounds até chegar o resultado
        """
        # define se o combate acabou
        em_combate = True

        # define a quantidade de turnos por round e ordem
        turnos = 3 * [self._turno_aloy] + [self._turno_maquinas]

        # Inicia o loop de combate
        while em_combate:
            # round
            for turno in turnos:
                # turno
                turno()
                # Verifica a condição de parada dos
                # loop (interno e externo)
                if (
                    self._maquinas.estao_todas_mortas
                    or self._guerreira.esta_morto
                    or (
                        self._guerreira.esta_sem_flechas
                        and turno == self._turno_maquinas
                    )
                ):
                    em_combate = False
                    break

    def _turno_aloy(self) -> None:
        """
        Ações da Aloy em seu turno
        """
        # recebe a ações da aloy do input
        (
            indice_alvo,
            parte,
            tipo_flecha,
            coord_x,
            coord_y,
        ) = input().split(", ")

        # Faz aloy usar a flecha
        self._guerreira.usar_flecha(tipo_flecha)

        # Seleciona a maquina alvo dentro da lista de Máquias
        alvo = self._maquinas[int(indice_alvo)]

        # Seleciona a parte alvo da máquina
        parte_alvo: Parte_maquina = alvo.fraquezas[parte]

        # Calcula o dano causado pela flecha
        dano = self._calcular_dano(
            parte_alvo, tipo_flecha, tuple((int(coord_x), int(coord_y)))
        )

        # Da dano na máquina
        alvo.tomar_dano(dano)

        # Verifica se o alvo morreu
        if alvo.esta_morto:
            # Coloca o acontecimento no registro de combate
            self._resgistro_do_combate.append(
                "Máquina " + indice_alvo + " derrotada"
            )

    def _turno_maquinas(self) -> None:
        """
        Executa as ações predeterminadas das máquinas
        """
        # Da dano a Aloy com a soma dos pontos_de_ataque
        # das máquinas no combate e que não morreram
        self._guerreira.tomar_dano(
            sum(
                [
                    maquina.pontos_de_ataque
                    for maquina in self._maquinas
                    if not maquina.esta_morto
                ]
            )
        )

    def _calcular_dano(
        self,
        parte: Parte_maquina,
        tipo_flecha: str,
        coordenada_flecha: tuple[int, ...],
    ) -> int:
        """
        Calcula o dano causado por uma flecha
        baseado no tipo da fleca e no ponto da parte
        alvo
        conta crítico automaticamente
        """
        # Define o dano como o dano_max inicialmente
        dano = parte.dano_max

        # Calcula a quantiadade de dano a ser removido
        # em relação ao ponto que a flecha acertou
        coord_flecha_x, coord_flecha_y = coordenada_flecha
        coord_fraqueza_x, coord_fraqueza_y = parte.coordenada
        subtrai_dano: int = -(
            abs(coord_fraqueza_x - coord_flecha_x)
            + abs(coord_fraqueza_y - coord_flecha_y)
        )

        # Verifica se o acerto é crítico
        if not subtrai_dano:
            parte.somar_critico()
        else:
            dano += subtrai_dano
        # Verifica se a parte é vunerável a qualquer flecha
        parte_eh_vuneravel: bool = parte.fraqueza == "todas"

        # Verifica se a parte não é vunerável a qualquer flecha
        parte_eh_invuneravel: bool = parte.fraqueza == "nenhuma"

        # Verifica se a parte é vunerável a flecha disparada
        fraqueza_eq_tipo_flecha: bool = parte.fraqueza == tipo_flecha

        # Verifica se a parte tem resistência sobre o tipo da flecha
        if parte_eh_invuneravel or (
            not fraqueza_eq_tipo_flecha and not parte_eh_vuneravel
        ):
            dano //= 2

        # Retorna o dano
        return dano if dano > 0 else 0

    def resultado(self) -> str:
        """
        Retorna a resultado completo do combate
        """
        return "\n".join(
            texto
            for texto in [
                str(self),
                str(self._guerreira),
                str(self._maquinas),
            ]
            if texto
        )

    def __str__(self) -> str:
        """
        Retorna o resultado parcial do combate
        Vida inicial, Abates de máquinas e Vida após o combate
        """
        self._resgistro_do_combate.append(
            "Vida após o combate = " + str(self._guerreira.vida)
        )
        return "\n".join(self._resgistro_do_combate)


# Fim Classes

main() if __name__ == "__main__" else None
