# Incico Princial

def main():
    genoma = [*input()]
    comando = [""]
    while comando[0] != "sair":
        comando = input().split()
        match comando[0]:
            case "reverter":
                genoma = reverter(genoma,
                                  int(comando[1]), int(comando[2]))
            case "transpor":
                genoma = transpor(genoma,
                                  int(comando[1]),
                                  int(comando[2]),
                                  int(comando[3]))
            case "combinar":
                genoma = combinar(genoma,
                                  comando[1], int(comando[2]))
            case "concatenar":
                genoma = concatenar(genoma,
                                    comando[1])
            case "remover":
                genoma = remover(genoma,
                                 int(comando[1]), int(comando[2]))
            case "transpor_e_reverter":
                genoma = transpor_e_reverter(genoma,
                                             int(comando[1]),
                                             int(comando[2]),
                                             int(comando[3]))
            case "buscar":
                print(buscar(genoma,
                             comando[1]))
            case "buscar_bidirecional":
                print(buscar_bidirecional(genoma,
                                          comando[1]))
            case "mostrar":
                mostrar(genoma)
            case "sair":
                break
            case _:
                print("ERROR: OPÇÃO INVALIDA!!!")

# Fim Princial

# Início Funções

# <lista>[<início (intervalo fechado)>:<fim (intervalo aberto)>:<passo>]
# <lista>[::-1] retorna a lista de traz pra frente
# <lista>[:j] retorna uma sublista do iníco até o j em incluir o j
# <lista>[i:] retorna uma sublista do i até o fim da lista, contendo i
# <lista>[i:j] retorna uma sublista no intervalo [i,j)


def reverter(gen_ref: list[str], i: int, j: int) -> list[str]:
    # <lista>[i:j:-1] retorna a lista de traz pra frente no intervalo [i,j)
    # por a lista estar de invetida, i>j e sendo o fim um intervalo aberto,
    # precisa de um inline if para acessar o primeiro íncide
    return gen_ref[:i] + gen_ref[j:i-1 if i > 0 else None:-1] + gen_ref[j+1:]


def transpor(gen_ref: list[str], i: int, j: int, k: int) -> list[str]:
    return gen_ref[:i] + gen_ref[j+1:k+1] + gen_ref[i:j+1] + gen_ref[k+1:]


def combinar(gen_ref: list[str], genoma_a_combinar: str, i: int) -> list[str]:
    return gen_ref[:i] + [*genoma_a_combinar] + gen_ref[i:]


def concatenar(gen_ref: list[str], genoma_a_concatenar: str) -> list[str]:
    return gen_ref + [*genoma_a_concatenar]


def remover(gen_ref: list[str], i: int, j: int) -> list[str]:
    return gen_ref[:i] + gen_ref[j+1:]


def transpor_e_reverter(gen_ref: list[str], i: int,
                        j: int, k: int) -> list[str]:
    return reverter(transpor(gen_ref, i, j, k), i, k)


def buscar(gen_ref: list[str], genoma_pesquisa: str) -> int:
    return int((''.join(gen_ref)).count(genoma_pesquisa))


def buscar_bidirecional(gen_ref: list[str], genoma_pesquisa: str) -> int:
    return (buscar(gen_ref, genoma_pesquisa) +
            buscar(gen_ref[::-1], genoma_pesquisa))


def mostrar(gen_ref) -> None:
    print(*gen_ref, sep="")


# Fim Funções

main() if __name__ == "__main__" else None
