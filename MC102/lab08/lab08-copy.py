def main() -> None:
    # Início Declaração de variáveis
    lista_categorias_simples = [
        "filme que causou mais bocejos",
        "filme que foi mais pausado",
        "filme que mais revirou olhos",
        "filme que não gerou discussão nas redes sociais",
        "enredo mais sem noção",
    ]
    # categorias_especiais = [
    #     "prêmio pior filme do ano",
    #     "prêmio não merecia estar aqui",
    # ]

    # Fim Declaração de variáveis
    # Início Entrada
    lista_filmes: list[str] = [input() for _ in range(int(input()))]

    dict_avaliacoes: dict[tuple[str, str], list[tuple[int, str]]] = {}
    for _ in range(int(input())):
        avaliador, categoria, nome_filme, nota = input().split(", ")

        if not ((categoria, nome_filme) in dict_avaliacoes):
            dict_avaliacoes[(categoria, nome_filme)] = []

        dict_avaliacoes[(categoria, nome_filme)].append((int(nota), avaliador))
    """dict_avaliacoes é um dicionário com chave tupla com o
    nome da categoria e nome do fime
    e valor lista de tupla com a nota e o nome do avaliador"""
    # Início Processamento
    ganhadores_categorias_simples: dict[str, tuple[str, float, int]] = {
        categoria: ganhador_categoria_simples(
            {
                filme: valor
                for (_categoria, filme), valor in dict_avaliacoes.items()
                if _categoria == categoria
            }
        )
        for categoria in lista_categorias_simples
    }
    ganhadores_categorias_especiais: dict[str, str] = {
        "prêmio pior filme do ano": ganhador_pior_filme_do_ano(
            [
                (nome_filme, nota, n_avaliadores)
                for _, (
                    nome_filme,
                    nota,
                    n_avaliadores,
                ) in ganhadores_categorias_simples.items()
            ]
        ),
        "prêmio não merecia estar aqui": ganhadores_nao_merecia_estar_aqui(
            lista_filmes, dict_avaliacoes
        ),
    }

    # Fim Processamento
    # Início Saída
    print("#### abacaxi de ouro ####", end="\n\n")
    print("categorias simples")
    for categoria, (nome_filme, _, _) in ganhadores_categorias_simples.items():
        print(
            "categoria: ",
            categoria,
            "\n- ",
            nome_filme,
            sep="",
        )
    # [
    #     print("categoria: ", categoria, "\n- ", nome_filme, sep="")
    #     for categoria, (
    #         nome_filme,
    #         _,
    #         _,
    #     ) in ganhadores_categorias_simples.items()
    # ]
    print("\ncategorias especiais")
    for categoria, (nome_filme) in ganhadores_categorias_especiais.items():
        print(
            categoria,
            "\n- ",
            nome_filme,
            sep="",
        )
    # [
    #     print(categoria, "\n- ", nome_filme, sep="")
    #     for categoria, nome_filme in ganhadores_categorias_especiais.items()
    # ]
    # Fim Saída


def ganhador_categoria_simples(
    filmes_na_categoria: dict[str, list[tuple[int, str]]]
) -> tuple[str, float, int]:
    """Calcula a ganhador de categoria simples,
    retorna tupla com nome do filme nota e numero de avaliadores"""
    # Calulando as notas dos filmes
    notas_filmes: list[tuple[str, float, int]] = [
        (
            nome_filme,
            sum([nota for nota, _ in avaliacoes]) / len(avaliacoes),
            len(set([avaliador for _, avaliador in avaliacoes])),
        )
        for nome_filme, avaliacoes in filmes_na_categoria.items()
    ]
    # Definindo o ganhador
    # ganhador: tuple[str, float, int] = (str(), float(), int())
    ganhador: tuple[str, float, int] = notas_filmes[0]
    for nome_filme, nota, n_avaliadores in notas_filmes[1:]:
        _, nota_ganhador, n_avaliadores_ganhador = ganhador
        eh_nota_maior: bool = nota > nota_ganhador
        eh_empate: bool = nota == nota_ganhador
        eh_numeros_avaliadores_maior: bool = (
            n_avaliadores > n_avaliadores_ganhador
        )
        if eh_nota_maior or (eh_empate and eh_numeros_avaliadores_maior):
            ganhador = (nome_filme, nota, n_avaliadores)
    return ganhador


def ganhador_pior_filme_do_ano(
    ganhadores_simples: list[tuple[str, float, int]]
) -> str:
    """Define o ganhador de pior filme do ano
    retorna o nome do filme ganhador"""
    filmes_ganhadores: list[str] = [
        nome_filme for nome_filme, _, _ in ganhadores_simples
    ]
    filmes_avaliados: list[str] = list(set(filmes_ganhadores))
    numeros_de_categorias_ganhas = [
        (
            nome_filme,
            filmes_ganhadores.count(nome_filme),
            sum(
                [
                    nota
                    for _nome_filme, nota, _ in ganhadores_simples
                    if nome_filme == _nome_filme
                ]
            ),
        )
        for nome_filme in filmes_avaliados
    ]

    ganhador: tuple[str, int, float] = numeros_de_categorias_ganhas[0]
    for (
        nome_filme,
        n_de_categorias_ganhas,
        soma_das_notas,
    ) in numeros_de_categorias_ganhas[1:]:
        (
            _,
            n_de_categorias_ganhas_do_ganhador,
            soma_das_notas_ganhador,
        ) = ganhador

        eh_numero_categorias_ganhas_maior: bool = (
            n_de_categorias_ganhas > n_de_categorias_ganhas_do_ganhador
        )
        eh_empate: bool = (
            n_de_categorias_ganhas == n_de_categorias_ganhas_do_ganhador
        )
        eh_soma_das_notas_maior: bool = (
            soma_das_notas > soma_das_notas_ganhador
        )

        if eh_numero_categorias_ganhas_maior or (
            eh_empate and eh_soma_das_notas_maior
        ):
            ganhador = (nome_filme, n_de_categorias_ganhas, soma_das_notas)
    return ganhador[0]


def ganhadores_nao_merecia_estar_aqui(
    lista_filmes: list[str],
    dict_avaliacoes: dict[tuple[str, str], list[tuple[int, str]]],
) -> str:
    """Define o ganhadores do premio nao merecia estar aqui
    retorna string formatada com os vencedores, ex: 'filme 1, filme2, filme3',
    caso n tenha filmes ganhadores retora sting com o texto:'sem ganhadores'"""
    # verifica filmes que não tiveram avaliações
    ganhadores: list[str] = [
        filme
        for filme in lista_filmes
        if not (filme in [chave[1] for chave, _ in dict_avaliacoes.items()])
    ]
    # retorna string única com a lista
    if not (ganhadores):
        return "sem ganhadores"
    return ", ".join(ganhadores)


main() if __name__ == "__main__" else None
