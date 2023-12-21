# Inicio Imports
import sys
from typing import Any, Callable

# Fim Imports

# Inicio config recursion limit
sys.setrecursionlimit(16385)
# Fim config recursion limit


# Inicio main
def main() -> None:
    # Inicio entrada

    # Instancia a imagem
    imagem: Imagem = Imagem(input())

    # Executa os comandos da entrada
    for _ in range(int(input())):
        imagem.executar_comando_de_texto(input())

    # Fim entrada


# Fim main


# Inicio Classes
class Imagem:
    def __init__(self, path: str) -> None:
        # abre o arquivo da imagem
        with open(path, "r", encoding="utf-8") as imagem:
            # ler a versao do formato pghm
            self._versao: str = imagem.readline()

            # ler o comentario do software que exportou o arquivo
            self._comentario: str = imagem.readline()

            # ler a dimensoes da imagem
            numero_de_colunas, numero_de_linhas = map(
                int, imagem.readline().split()
            )
            self._dimensoes: tuple[int, int] = (
                numero_de_colunas,
                numero_de_linhas,
            )

            # ler a _intensidade_de_cor da imagem
            self._intensidade_de_cor = int(imagem.readline())

            # ler a matriz de pixeis
            self._matriz: list[list[int]] = [
                [int(pixel) for pixel in imagem.readline().split()]
                for _ in range(self._dimensoes[1])
            ]

        # Dicioraio de funcoes definidas e seus tradutores de argumentos
        self._comandos_definidos: dict[
            str, tuple[Callable[..., None], Callable[..., Any]]
        ] = {
            "bucket": (
                self.balde_de_tinha,
                lambda cor, tolerancia, coluna_pixel, linha_pixel: [
                    int(cor),
                    int(tolerancia),
                    (int(coluna_pixel), int(linha_pixel)),
                ],
            ),
            "negative": (
                self.negativo,
                lambda tolerancia, coluna_pixel, linha_pixel: [
                    int(tolerancia),
                    (int(coluna_pixel), int(linha_pixel)),
                ],
            ),
            "cmask": (
                self.mascara_complementar,
                lambda tolerancia, coluna_pixel, linha_pixel: [
                    int(tolerancia),
                    (int(coluna_pixel), int(linha_pixel)),
                ],
            ),
            "save": (self.salvar_imagem, lambda path: [path]),
        }

        # Define a mensagem de erro caso o comando nao
        # seja encontrado no dicionario
        self._comando_nao_encontrado: tuple[
            Callable[..., None], Callable[..., Any]
        ] = (
            print,
            lambda: ["Comando não encontrado"],
        )

        # Define dos vetores de direção para a busca de regioes conexas
        self._vetores_direcao = self._combinacao([-1, 0, 1], 2)
        # Remove da combinacao o vetor nulo
        self._vetores_direcao.remove([0, 0])

    def executar_comando_de_texto(self, comando_texto: str) -> None:
        """
        Executa uma função de acordo com o comando de texto
        <comando> <arg1> <arg2> <arg3>
        """
        # Recece o comando e os argumentos
        entrada = comando_texto.split(maxsplit=1)
        if len(entrada) == 1:
            entrada.append("__sem_argumentos__")

        # Descompacta a entrada
        comando, argumentos = entrada

        # Procura no dicionario o comandoo
        funcao_do_comando, parser_argumentos = self._comandos_definidos.get(
            comando, self._comando_nao_encontrado
        )

        # Passa os valor da entrada para o tipo certo
        argumentos = parser_argumentos(*argumentos.split())

        # Executa o comando
        funcao_do_comando(*argumentos)

    def pintar_pixel(self, cor: int, pixel: tuple[int, int]) -> None:
        """
        Escreve em um pixel uma nova cor
        """
        coluna, linha = pixel
        self._matriz[linha][coluna] = cor

    def cor_pixel(self, pixel: tuple[int, int]) -> int:
        """
        Retorna a cor de um pixel
        """
        coluna, linha = pixel
        return self._matriz[linha][coluna]

    def _combinacao(
        self, lista_de_items: list[Any], numero_digitos: int
    ) -> list[list[Any]]:
        """
        Retorna uma lista com lista de cada combinacao
        dos items da lista_de_items de em n
        numero_digitos(numero de items da combinacao)
        """
        if numero_digitos == 1:
            return [[item] for item in lista_de_items]
        else:
            return [
                [primeiro_digito, *outros_digitos]
                for primeiro_digito, outros_digitos in zip(
                    [
                        lista_de_items[
                            i // (len(lista_de_items) ** (numero_digitos - 1))
                        ]
                        for i in range((len(lista_de_items) ** numero_digitos))
                    ],
                    self._combinacao(lista_de_items, numero_digitos - 1)
                    * len(lista_de_items),
                )
            ]

    def _pixeis_dos_arredores(
        self, pixel: tuple[int, int]
    ) -> list[tuple[int, int]]:
        """
        Retorna uma lista com os pixeis dos pontos ao redor de um pixel
        """
        coluna_pixel_ref, linha_pixel_ref = pixel
        limite_coluna, limite_linha = self._dimensoes

        return [
            (
                coluna_pixel_ref + direcao_coluna,
                linha_pixel_ref + direcao_linha,
            )
            for direcao_coluna, direcao_linha in self._vetores_direcao
            if 0 <= (coluna_pixel_ref + direcao_coluna) < limite_coluna
            and 0 <= (linha_pixel_ref + direcao_linha) < limite_linha
        ]

    def balde_de_tinha(
        self,
        cor: int,
        tolerancia: int,
        pixel: tuple[int, int],
        cor_pixel_seed: int = -1,
    ) -> None:
        """
        Preenche regiões conexas a uma pixel semente com uma cor definida
        """
        if cor_pixel_seed == -1:
            cor_pixel_seed = self.cor_pixel(pixel)
        self.pintar_pixel(cor, pixel)

        for pixel_atual in self._pixeis_dos_arredores(pixel):
            cor_pixel_atual = self.cor_pixel(pixel_atual)
            if (
                abs(cor_pixel_atual - cor_pixel_seed) <= tolerancia
                and cor_pixel_atual != cor
            ):
                self.balde_de_tinha(
                    cor, tolerancia, pixel_atual, cor_pixel_seed
                )

    def negativo(self, tolerancia: int, pixel: tuple[int, int]) -> None:
        """
        Inverte as cores das pixeis conexos a um pixel semente semente
        """
        cor_pixel_seed = self.cor_pixel(pixel)
        cor_negativa = self._intensidade_de_cor - cor_pixel_seed
        self.pintar_pixel(cor_negativa, pixel)

        for pixel_atual in self._pixeis_dos_arredores(pixel):
            cor_pixel_atual = self.cor_pixel(pixel_atual)
            if abs(cor_pixel_atual - cor_pixel_seed) <= tolerancia:
                self.negativo(tolerancia, pixel_atual)

    def mascara_complementar(
        self, tolerancia: int, pixel: tuple[int, int]
    ) -> None:
        """
        Modifica a imagem para uma imagem binaria (mascara)
        contendo 0 nos pixeis pertentes a regiao de pixeis conexa contendo
        o pixel semente, e 255 nas demais pixeis nao-conexas
        """
        self.balde_de_tinha(-1, tolerancia, pixel)

        for countador_linha in range(len(self._matriz)):
            for contador_coluna in range(len(self._matriz[0])):
                if self._matriz[countador_linha][contador_coluna] != -1:
                    self.pintar_pixel(255, (contador_coluna, countador_linha))

        self.balde_de_tinha(0, 1, pixel)

    def salvar_imagem(self, path: str = "") -> None:
        """
        Printa a imagem no terminal
        ou salva a imagem no local passado por parametro
        """
        if path == "__sem_argumentos__":
            print(self, end="")
        else:
            with open(path, "w", encoding="utf-8") as imagem:
                imagem.write(str(self))

    def __str__(self) -> str:
        """
        Retorna a string do arquivo de imagem
        no formtato pgm
        """
        return (
            self._versao
            + "# Imagem criada pelo lab13\n"
            + " ".join(map(str, list(self._dimensoes)))
            + "\n"
            + str(self._intensidade_de_cor)
            + "\n"
            + "\n".join(
                [
                    " ".join([str(pixel) for pixel in linha])
                    for linha in self._matriz
                ]
            )
            + "\n"
        )


# Fim Classes

main() if __name__ == "__main__" else None
