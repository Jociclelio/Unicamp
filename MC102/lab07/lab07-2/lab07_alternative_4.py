from collections.abc import Callable


def main() -> None:
    ascii_visivel = [chr(i) for i in range(32, 127)]
    ascii_dict = {ascii_visivel[i]: i for i in range(len(ascii_visivel))}
    # Incio entradas

    operador, operando1, operando2 = input(), input(), input()
    entrada = [[*input()] for _ in range(int(input()))]

    # Fim entradas
    # Inicio Cálculo da chave criptográfica

    entrada_str = "".join(["".join(linha) for linha in entrada])
    indice_opr1 = primeiro_indice(entrada_str, operando1)
    indice_opr2 = primeiro_indice(entrada_str, operando2, indice_opr1)
    chave_crpt = calcular_chave(indice_opr1, indice_opr2, operador)

    # Fim Cálculo da chave criptográfica
    # Inicio Descriptografia

    # Descriptgrafa o texto, texto_descrpt é uma lista com strings
    # como por exemplo:
    #     ["<linha um descriptografada>",
    #      "<linha dois descriptografada>",
    #      ...
    #      "<linha ultima linha descriptografada>"]

    texto_descrpt: list[str] = [
        "".join(
            [
                ascii_visivel[
                    indice_congruente(
                        ascii_dict[carac] + chave_crpt, len(ascii_visivel)
                    )
                ]
                for carac in linha
            ]
        )
        for linha in entrada
    ]

    # Fim Descriptografia
    # Inicio Saida

    print(chave_crpt)
    print(*texto_descrpt, sep="\n")

    # Fim Saida


def calcular_chave(valor1: int, valor2: int, operacao: str) -> int:
    """
    calcular a chave com base os valor1 e valor2 e a operacao
    retorna inteiro
    """
    match operacao:
        case "+":
            return valor1 + valor2
        case "-":
            return valor1 - valor2
        case "*":
            return valor1 * valor2
    raise ValueError("Operacao inválida")


def primeiro_indice(string: str, buscar: str, inicio: int = 0) -> int:
    """
    retorna o primeiro indice onde buscar é encontrado em string
    retorna -1 caso não encontre
    """
    vogais = "AEIOUaeiou"
    dict_buscar: dict[str, Callable[[str], bool]] = {
        "numero": lambda s: s.isnumeric(),
        "vogal": lambda s: s in vogais,
        "consoante": lambda s: s.isalpha() and s not in vogais,
    }
    for i in range(inicio, len(string)):
        if dict_buscar.get(buscar, lambda s: s in buscar)(string[i]):
            return i
    return -1


def indice_congruente(indice: int, high: int) -> int:
    """
    (indice_congruente)
    retorna valores entre 0 e high-1
    de forma que :
        (high, high) -> 0
        (high + 1, high) -> 1
        (2*high, high) -> 0
        (2*high + 1,high) -> 1
    """
    if indice >= 0:
        return indice % high
    else:
        return indice_congruente(
            indice + high * (((-1 * indice) // high) + 1), high
        )


main() if __name__ == "__main__" else None
