def loc(i: int, j: int) -> str:
    if i == j:
        return "empate"
    elif i > j:
        return "Jornada nas Estrelas" if (i + j) % 2 == 0 else "Interestelar"
    else:
        return "Interestelar" if (i + j) % 2 == 1 else "Jornada nas Estrelas"


jogo_para_indice = {
    "pedra": 0,
    "papel": 1,
    "tesoura": 2,
    "lagarto": 3,
    "spock": 4,
}
escolhaSheila, escolhaReginaldo = (
    jogo_para_indice[input()],
    jogo_para_indice[input()],
)
print(loc(escolhaSheila, escolhaReginaldo))
