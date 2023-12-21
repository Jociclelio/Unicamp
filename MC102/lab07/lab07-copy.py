def main() -> None:

    ascii_imprimivel = [chr(i) for i in range(32, 127)]
    operador = input()
    operando1 = input()
    operando2 = input()
    entrada: list[list[str]] = []
    entradastr = ""
    for i in range(int(input())):
        linha = [*input()]
        entrada.append(linha)
        entradastr += ''.join(linha)
    indice_operando1 = primeiro_indice(entradastr, operando1)
    indice_operando2 = indice_operando1 + primeiro_indice(
            entradastr[indice_operando1:], operando2)
    chave_criptografica = eval(str(indice_operando1) + operador +
                               str(indice_operando2))
    print(chave_criptografica)
    for linha in entrada:
        print(sep="", *[*[ascii_imprimivel[indice_range_limit(
            ascii_imprimivel.index(caracetere) + chave_criptografica,
            0, len(ascii_imprimivel))] for caracetere in linha]])


def primeiro_indice(texto_completo: str, buscar: str) -> int:
    vogais = ["A", "a", "E", "e", "I", "i", "O", "o", "I", "i"]
    numeros = ["0", "1", "2", "3", "4", "5", "7", "8", "9"]
    consoantes = ["B", "b", "C", "c", "D", "d", "F", "f", "G", "g", "H", "h",
                  "J", "j", "K", "k", "L", "l", "M", "m", "N", "n", "P", "p",
                  "Q", "q", "R", "r", "S", "s", "T", "t", "V", "v", "W", "w",
                  "X", "x", "Y", "y", "Z", "z"]
    procura = []
    match buscar:
        case "vogal": procura = vogais
        case "consoantes": procura = consoantes
        case "numero": procura = numeros
        case _: procura = [buscar]
    for i in range(len(texto_completo)):
        if texto_completo[i] in procura:
            return i
    return 0


def indice_range_limit(indice: int, low: int, high: int):
    if indice >= low:
        return indice % high
    else:
        return indice_range_limit(indice+high, low, high)


main() if __name__ == "__main__" else None
