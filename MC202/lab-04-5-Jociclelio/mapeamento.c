#include "./matriz.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Reduz uma ordem no tamanho da matriz de inteiros quadrada em 1
 * A matriz resultado eh a submatriz de ordem matriz_tamanho-1 com
 * maior soma de seus respectivos inteiros
 *
 * Imprimi a matriz e pergunta se o stdin quer alterar o valor
 * de algum indice da matriz
 * se sim, altera e executa a funcao novamente
 * se nao, nao faz nada e a funcao acaba
 */
void procura_de_area_critica_recursiva(int **matriz, int submatriz_tamanho,
                                       int sub_linha, int sub_coluna) {
  if (submatriz_tamanho > 1) {
    /*
     * comecamos somando somente os valores da linha e coluna sem as pontas
     */
    int linha_inferior, linha_superior, coluna_esquerda, coluna_direita;
    linha_superior = soma_sublinha(matriz, 1, submatriz_tamanho - 1, 0,
                                   sub_linha, sub_coluna);
    linha_inferior =
        soma_sublinha(matriz, 1, submatriz_tamanho - 1, submatriz_tamanho - 1,
                      sub_linha, sub_coluna);
    coluna_esquerda = soma_subcoluna(matriz, 1, submatriz_tamanho - 1, 0,
                                     sub_linha, sub_coluna);
    coluna_direita =
        soma_subcoluna(matriz, 1, submatriz_tamanho - 1, submatriz_tamanho - 1,
                       sub_linha, sub_coluna);
    /*
     * agora calculamos as bordas de de cada submatriz
     */
    int soma_superior_esquerdo, soma_superior_direito, soma_inferior_esquerdo,
        soma_inferior_direito;
    soma_superior_esquerdo =
        matriz[sub_linha][sub_coluna] + linha_superior + coluna_esquerda;
    soma_superior_direito =
        matriz[sub_linha][sub_coluna + submatriz_tamanho - 1] + linha_superior +
        coluna_direita;
    soma_inferior_esquerdo =
        matriz[sub_linha + submatriz_tamanho - 1][sub_coluna] + linha_inferior +
        coluna_esquerda;
    soma_inferior_direito = matriz[sub_linha + submatriz_tamanho - 1]
                                  [sub_coluna + submatriz_tamanho - 1] +
                            linha_inferior + coluna_direita;
    /*
     * calcula se a submatriz de maior soma esta na direita da matriz maior
     */
    if ((soma_superior_direito > soma_superior_esquerdo ||
         soma_inferior_direito > soma_superior_esquerdo) &&
        (soma_superior_direito > soma_inferior_esquerdo ||
         soma_inferior_direito > soma_inferior_esquerdo))
      sub_coluna++;

    /*
     * calcula se a submatriz de maior soma esta para baixo na matriz maior
     */
    if ((soma_inferior_esquerdo > soma_superior_esquerdo ||
         soma_inferior_direito > soma_superior_esquerdo) &&
        (soma_inferior_esquerdo > soma_superior_direito ||
         soma_inferior_direito > soma_superior_direito))
      sub_linha++;

    submatriz_tamanho--;

    printf("\nConjuntos que precisam de atenção:\n");
    imprimir_submatriz_quadrada(matriz, submatriz_tamanho, sub_linha,
                                sub_coluna);

    int eh_para_ter_alteracao = 0;
    scanf("%d ", &eh_para_ter_alteracao);
    if (eh_para_ter_alteracao) {
      editar_submatriz_de_stdin(matriz, sub_linha, sub_coluna);
      procura_de_area_critica_recursiva(matriz, submatriz_tamanho, sub_linha,
                                        sub_coluna);
    }
  }
}

/*
 * Chama a funcao recursiva passando como submatriz a matriz
 */
void procura_de_area_critica(int **matriz, int matriz_tamanho) {
  procura_de_area_critica_recursiva(matriz, matriz_tamanho, 0, 0);
}

int main() {
  int **matriz, matriz_tamanho;

  scanf("%d ", &matriz_tamanho);
  matriz = malloc(matriz_tamanho * sizeof(int *));

  for (int i = 0; i < matriz_tamanho; i++) {
    matriz[i] = malloc(matriz_tamanho * sizeof(int));
    for (int j = 0; j < matriz_tamanho; j++) {
      scanf("%d ", &matriz[i][j]);
    }
  }

  printf("Quadras:\n");
  imprimir_matriz_quadrada(matriz, matriz_tamanho);
  /*
   * funcao recursiva
   */
  procura_de_area_critica(matriz, matriz_tamanho);

  for (int i = 0; i < matriz_tamanho; i++)
    free(matriz[i]);
  free(matriz);
  return 0;
}
