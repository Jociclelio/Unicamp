def paraIndice(escolha):  # função que traduz a escolha para índice de lista
    if escolha == "pedra":
        return 0
    if escolha == "papel":
        return 1
    if escolha == "tesoura":
        return 2
    if escolha == "lagarto":
        return 3
    if escolha == "spock":
        return 4


jogo = [
    [
        "empate",
        "Jornada nas Estrelas",
        "Interestelar",
        "Interestelar",
        "Jornada nas Estrelas",
    ],  # lista jogo tal que linhas e colunas são as escolhas
    [
        "Interestelar",
        "empate",
        "Jornada nas Estrelas",
        "Jornada nas Estrelas",
        "Interestelar",
    ],  # de Sheila(linhas) e Reginaldo(colunas)
    [
        "Jornada nas Estrelas",
        "Interestelar",
        "empate",
        "Interestelar",
        "Jornada nas Estrelas",
    ],  #
    [
        "Jornada nas Estrelas",
        "Interestelar",
        "Jornada nas Estrelas",
        "empate",
        "Interestelar",
    ],
    [
        "Interestelar",
        "Jornada nas Estrelas",
        "Interestelar",
        "Jornada nas Estrelas",
        "empate",
    ],
]
escolhaSheila, escolhaReginaldo = paraIndice(input()), paraIndice(
    input()
)  # recebe as escolhas de Sheila e Reginaldo passando para o formato de índice
print(jogo[escolhaSheila][escolhaReginaldo])  # beba água se está lendo isso
