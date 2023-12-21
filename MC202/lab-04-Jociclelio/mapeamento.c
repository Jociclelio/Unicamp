#include <stdio.h>
#include <stdlib.h>

/*
 * Imprimi uma matriz quadrada de inteiros stdout
 */
void imprimir_matriz_quadrada(int **matriz, int matriz_tamanho) {
  for (int i = 0; i < matriz_tamanho; i++) {
    for (int j = 0; j < matriz_tamanho; j++)
      printf("%d\t", matriz[i][j]);
    printf("\n");
  }
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
 * Edita um valor na matriz de inteiros passado por parametro
 */
void editar_matriz_de_stdin(int **matriz) {
  int i = 0, j = 0, valor = 0;
  if (scanf("%d %d %d ", &i, &j, &valor))
    matriz[i][j] = valor;
}

/*
 * Reduz uma ordem no tamanho da matriz de inteiros quadrada em 1
 * A matriz resultado eh a submatriz de ordem menor com maior soma
 * de seus respectivos inteiros
 *
 * Imprimi a matriz e perguanta se o stdin quer alterar o valor
 * de algum indice
 * se sim, altera e executa a funcao novamente
 * se nao, nao faz nada
 */
void procura_de_area_critica(int **matriz, int matriz_tamanho) {
  if (matriz_tamanho > 1) {
    int linha_superior = soma_linha(matriz, 1, matriz_tamanho - 1, 0),
        linha_inferior =
            soma_linha(matriz, 1, matriz_tamanho - 1, matriz_tamanho - 1),
        coluna_esquerda = soma_coluna(matriz, 1, matriz_tamanho - 1, 0),
        coluna_direita =
            soma_coluna(matriz, 1, matriz_tamanho - 1, matriz_tamanho - 1);
    int soma_superior_esquerdo =
            matriz[0][0] + linha_superior + coluna_esquerda,
        soma_superior_direito =
            matriz[0][matriz_tamanho - 1] + linha_superior + coluna_direita,
        soma_inferior_esquerdo =
            matriz[matriz_tamanho - 1][0] + linha_inferior + coluna_esquerda,
        soma_inferior_direito = matriz[matriz_tamanho - 1][matriz_tamanho - 1] +
                                linha_inferior + coluna_direita;

    if ((soma_superior_direito > soma_superior_esquerdo ||
         soma_inferior_direito > soma_superior_esquerdo) &&
        (soma_superior_direito > soma_inferior_esquerdo ||
         soma_inferior_direito > soma_inferior_esquerdo)) {
      // shift direita ->
      for (int i = 0; i < matriz_tamanho; i++)
        matriz[i]++;
    }

    if ((soma_inferior_esquerdo > soma_superior_esquerdo ||
         soma_inferior_direito > soma_superior_esquerdo) &&
        (soma_inferior_esquerdo > soma_superior_direito ||
         soma_inferior_direito > soma_superior_direito)) {
      // shift baixo \/
      matriz++;
    }

    matriz_tamanho--;

    printf("\nConjuntos que precisam de atenção:\n");
    imprimir_matriz_quadrada(matriz, matriz_tamanho);

    int eh_para_ter_alteracao = 0;
    scanf("%d ", &eh_para_ter_alteracao);
    if (eh_para_ter_alteracao) {
      editar_matriz_de_stdin(matriz);
      procura_de_area_critica(matriz, matriz_tamanho);
    }
  }
}

int main() {
  int **matriz, matriz_tamanho, *ponteiro_para_free_da_forma_certa;
  scanf("%d ", &matriz_tamanho);
  matriz = malloc(matriz_tamanho * sizeof(int *));
  matriz[0] = malloc(matriz_tamanho * matriz_tamanho * sizeof(int));
  ponteiro_para_free_da_forma_certa = matriz[0];

  for (int i = 0; i < matriz_tamanho; i++) {
    matriz[i] = &matriz[0][i * matriz_tamanho];
    for (int j = 0; j < matriz_tamanho; j++) {
      scanf("%d ", &matriz[i][j]);
    }
  }

  printf("Quadras:\n");
  imprimir_matriz_quadrada(matriz, matriz_tamanho);
  procura_de_area_critica(matriz, matriz_tamanho);

  free(ponteiro_para_free_da_forma_certa);
  free(matriz);
  return 0;
}
