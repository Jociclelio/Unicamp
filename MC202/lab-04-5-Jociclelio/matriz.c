#include "./matriz.h"
#include <stdio.h>
/*
 * Imprimi uma submatriz quadrada de inteiros stdout
 */
void imprimir_submatriz_quadrada(int **matriz, int submatriz_tamanho, int linha,
                                 int coluna) {
  for (int i = linha; i < linha + submatriz_tamanho; i++) {
    for (int j = coluna; j < coluna + submatriz_tamanho; j++)
      printf("%d\t", matriz[i][j]);
    printf("\n");
  }
}

/*
 * Chama a funcao imprimir_submatriz_quadrada passando a matriz
 * como submatriz
 */
void imprimir_matriz_quadrada(int **matriz, int matriz_tamanho) {
  imprimir_submatriz_quadrada(matriz, matriz_tamanho, 0, 0);
}

/*
 * Retorna a soma de uma coluna de uma matriz de interios
 * Parametros:
 * int **matriz -> Matriz para soma
 * int inicial -> Indice inicial para soma na coluna
 * int final -> Indice final para soma
 * int coluna -> Coluna j para soma
 */
int soma_coluna(int **matriz, int inicial, int final, int coluna) {
  int soma = 0;
  for (int i = inicial; i < final; i++)
    soma += matriz[i][coluna];
  return soma;
}

/*
 * Retorna a soma de uma coluna de uma matriz de interios
 * Parametros:
 * int **matriz -> Matriz para soma
 * int inicial -> Indice inicial para soma na coluna
 * int final -> Indice final para soma
 * int coluna -> Coluna j para soma
 * int sub_linha -> inicio_sublinha
 * int sub_coluna -> inicio_subcoluna
 */
int soma_subcoluna(int **matriz, int inicial, int final, int coluna,
                   int sub_linha, int sub_coluna) {
  return soma_coluna(matriz, sub_linha + inicial, sub_coluna + final,
                     sub_coluna + coluna);
}

/*
 * Retorna a soma de uma linha de uma matriz de interios
 * Parametros:
 * int **matriz -> Matriz para soma
 * int inicial -> Indice inicial para soma na linha
 * int final -> Indice final para soma
 * int linha -> linha j para soma
 */
int soma_linha(int **matriz, int inicial, int final, int linha) {
  int soma = 0;
  for (int j = inicial; j < final; j++)
    soma += matriz[linha][j];
  return soma;
}

/*
 * Retorna a soma de uma linha de uma matriz de interios
 * Parametros:
 * int **matriz -> Matriz para soma
 * int inicial -> Indice inicial para soma na linha
 * int final -> Indice final para soma
 * int linha -> linha j para soma
 * int sub_linha -> inicio_sublinha
 * int sub_coluna -> inicio_subcoluna
 */
int soma_sublinha(int **matriz, int inicial, int final, int linha,
                  int sub_linha, int sub_coluna) {
  return soma_linha(matriz, sub_coluna + inicial, sub_linha + final,
                    sub_linha + linha);
}

/*
 * Edita um valor na submatriz
 * onde a posicao i,j e o valor vem do stdin
 */
void editar_submatriz_de_stdin(int **matriz, int linha, int coluna) {
  int i = 0, j = 0, valor = 0;
  if (scanf("%d %d %d ", &i, &j, &valor))
    matriz[linha + i][coluna + j] = valor;
}
