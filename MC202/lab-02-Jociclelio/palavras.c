#include <stdio.h>
#include <stdlib.h>

/*
 * Calcula o tamanho de uma string
 *
 * retorna um inteiro com o tamanho calculado
 */
int get_tamanho(char *string) {
  int i;
  for (i = 0; string[i] != '\0'; i++) {
  }
  return i;
}

/*
 * Procura se uma string esta presente em uma linha i de uma matriz de
 * caracteres
 *
 * retorna 1 se encontrar e 0 caso contario
 */
int esta_na_linha(char **matriz, int linha, int linha_tamanho, char *string,
                  int string_tamanho) {
  for (int i = 0; linha_tamanho - i >= string_tamanho; i++) {
    for (int j = 0; matriz[linha][i + j] == string[j] && j < string_tamanho;
         j++)
      if (string[j + 1] == '\0')
        return 1;
  }
  return 0;
}

/*
 * Procura se uma string esta presente em uma coluna j de uma matriz de
 * caracteres
 *
 * retorna 1 se encontrar e 0 caso contario
 */
int esta_na_coluna(char **matriz, int coluna, int coluna_tamanho, char *string,
                   int string_tamanho) {
  for (int i = 0; coluna_tamanho - i >= string_tamanho; i++) {
    for (int j = 0; matriz[i + j][coluna] == string[j] && j < string_tamanho;
         j++)
      if (string[j + 1] == '\0')
        return 1;
  }
  return 0;
}

/*
 * Procura se uma string ou sua reversa esta presente numa matriz de
 * caracteres
 *
 * parametros:
 *  matriz: Matriz
 *  numero_de_linhas: Numero de linhas da matriz
 *  numero_de_colunas: Numero de colunas da matriz
 *  string: string a ser procurada na matriz
 *
 *
 * retorna 1 se encontrar e 0 caso contario
 */
int esta_na_matriz(char **matriz, int numero_de_linhas, int numero_de_colunas,
                   char *string) {
  int string_tamanho = get_tamanho(string);

  char *string_reversa = malloc((string_tamanho + 1) * sizeof(char));
  for (int j = 1; j <= string_tamanho; j++)
    string_reversa[j - 1] = string[string_tamanho - j];
  string_reversa[string_tamanho] = '\0';

  for (int linha_atual = 0; linha_atual < numero_de_linhas; linha_atual++) {
    if (esta_na_linha(matriz, linha_atual, numero_de_colunas, string,
                      string_tamanho) ||
        esta_na_linha(matriz, linha_atual, numero_de_colunas, string_reversa,
                      string_tamanho)) {
      free(string_reversa);
      return 1;
    }
  }
  for (int coluna_atual = 0; coluna_atual < numero_de_colunas; coluna_atual++) {
    if (esta_na_coluna(matriz, coluna_atual, numero_de_linhas, string,
                       string_tamanho) ||
        esta_na_coluna(matriz, coluna_atual, numero_de_linhas, string_reversa,
                       string_tamanho)) {
      free(string_reversa);
      return 1;
    }
  }

  free(string_reversa);
  return 0;
}

int main() {
  // Declaracao de variaveis
  int numero_de_linhas, numero_de_colunas, numero_de_palavras;
  char **tabela_de_carateres, **palavras, *buffer;

  // Entrada
  scanf("%d %d %d ", &numero_de_linhas, &numero_de_colunas,
        &numero_de_palavras);

  palavras = malloc(numero_de_palavras * sizeof(char *));
  tabela_de_carateres = malloc(numero_de_linhas * sizeof(char *));

  for (int i = 0; i < numero_de_linhas; i++) {
    tabela_de_carateres[i] = malloc(numero_de_colunas * sizeof(char));
    for (int j = 0; j < numero_de_colunas; j++)
      scanf("%c ", &tabela_de_carateres[i][j]);
  }

  buffer = malloc(21 * sizeof(char));
  for (int i = 0; i < numero_de_palavras; i++) {
    scanf("%s ", buffer);
    int buffer_tamanho = get_tamanho(buffer);
    palavras[i] = malloc((buffer_tamanho + 1) * sizeof(char));
    for (int j = 0; j <= buffer_tamanho; j++)
      palavras[i][j] = buffer[j];
  }
  free(buffer);

  // Saida
  for (int i = 0; i < numero_de_palavras; i++)
    if (esta_na_matriz(tabela_de_carateres, numero_de_linhas, numero_de_colunas,
                       palavras[i]))
      printf("A palavra %s está no texto!\n", palavras[i]);
    else
      printf("A palavra %s não está no texto!\n", palavras[i]);

  // Liberar memoria e fim do programa
  for (int i = 0; i < numero_de_linhas; i++)
    free(tabela_de_carateres[i]);
  for (int i = 0; i < numero_de_palavras; i++)
    free(palavras[i]);
  free(tabela_de_carateres);
  free(palavras);
  return 0;
}
