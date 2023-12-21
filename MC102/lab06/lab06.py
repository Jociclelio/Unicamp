# Início import


from typing import Callable, Any


# Fim inport

# Início Princial


def main() -> None:
    vetor_ref = ler_vetor()
    comando = ""
    comandos_definidos = [
        "soma_vetores",
        "subtrai_vetores",
        "multiplica_vetores",
        "divide_vetores",
        "multiplicacao_escalar",
        "n_duplicacao",
        "soma_elementos",
        "produto_interno",
        "multiplica_todos",
        "correlacao_cruzada",
        "fim",
    ]
    while comando != "fim":
        comando = input()
        if comando in comandos_definidos:
            match comando:
                case "soma_vetores":
                    vetor_ref = soma_vetores(vetor_ref, ler_vetor())
                case "subtrai_vetores":
                    vetor_ref = subtrai_vetores(vetor_ref, ler_vetor())
                case "multiplica_vetores":
                    vetor_ref = multiplica_vetores(vetor_ref, ler_vetor())
                case "divide_vetores":
                    vetor_ref = divide_vetores(vetor_ref, ler_vetor())
                case "multiplicacao_escalar":
                    vetor_ref = multiplicacao_escalar(
                        vetor_ref, ler_vetor()[0]
                    )
                case "n_duplicacao":
                    vetor_ref = n_duplicacao(vetor_ref, ler_vetor()[0])
                case "soma_elementos":
                    vetor_ref = [soma_elementos(vetor_ref)]
                case "produto_interno":
                    vetor_ref = [produto_interno(vetor_ref, ler_vetor())]
                case "multiplica_todos":
                    vetor_ref = multiplica_todos(vetor_ref, ler_vetor())
                case "correlacao_cruzada":
                    vetor_ref = correlacao_cruzada(vetor_ref, ler_vetor())
                case "fim":
                    break
            print(vetor_ref)
        else:
            print("Comando inválido")


# Fim Princial

# Início Funções


def ler_vetor() -> list[int]:
    return [int(item) for item in input().split(sep=",")]


def opera_vetores(
    operacao: Callable[[int, int], int],
    vetor1: list[int],
    vetor2: list[int],
    fill1: int = 0,
    fill2: int = 0,
) -> list[int]:
    return [
        operacao(
            vetor1[i] if i < len(vetor1) else fill1,
            vetor2[i] if i < len(vetor2) else fill2,
        )
        for i in range(max(len(vetor1), len(vetor2)))
    ]


def soma_vetores(vetor1: list[int], vetor2: list[int]) -> list[int]:
    return opera_vetores(lambda v1, v2: v1 + v2, vetor1, vetor2)


def subtrai_vetores(vetor1: list[int], vetor2: list[int]) -> list[int]:
    return opera_vetores(lambda v1, v2: v1 - v2, vetor1, vetor2)


def multiplica_vetores(vetor1: list[int], vetor2: list[int]) -> list[int]:
    return opera_vetores(
        lambda v1, v2: v1 * v2, vetor1, vetor2, fill1=1, fill2=1
    )


def divide_vetores(vetor1: list[int], vetor2: list[int]) -> list[int]:
    return opera_vetores(lambda v1, v2: v1 // v2, vetor1, vetor2, fill2=1)


def multiplicacao_escalar(vetor1: list[int], escalar: int) -> list[int]:
    return [escalar * item for item in vetor1]


def n_duplicacao(vetor: list[int], n: int) -> list[int]:
    return [vetor[i % len(vetor)] for i in range(len(vetor) * n)]


def soma_elementos(vetor: list[int]) -> int:
    return vetor[0] + soma_elementos(vetor[1:]) if vetor else 0


def produto_interno(vetor1: list[int], vetor2: list[int]) -> int:
    return soma_elementos(multiplica_vetores(vetor1, vetor2))


def multiplica_todos(vetor1: list[int], vetor2: list[int]) -> list[int]:
    return [
        soma_elementos(multiplicacao_escalar(vetor2, vetor1[i]))
        for i in range(len(vetor1))
    ]


def correlacao_cruzada(vetor1: list[int], mascara: list[int]) -> list[int]:
    return [
        produto_interno(vetor1[i : i + len(mascara)], mascara)
        for i in range(len(vetor1) - len(mascara) + 1)
    ]


# Fim Funções
main() if __name__ == "__main__" else None
