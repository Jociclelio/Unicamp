#include <stdio.h>
#include <stdlib.h>
#define LIMITE_DE_VENDAS 10000

struct maior_sequencia_consecutiva {
  int salada;
  int tamanho_da_sequencia;
};

struct contador_de_saladas {
  int salada5;
  int salada7;
  int salada10;
};

struct maior_sequencia_consecutiva
maior_sequencia_de_vendas(int vendas[], int numero_de_vendas) {
  /*
   * Funcao que busca maior sequencia de vendas de frutas em um vetor de vendas
   * de frutas
   *
   * Retorna um struct com a salada e o tamanho da maior sequencia
   */
  int tamanho_da_sequencia_atual = 1;
  struct maior_sequencia_consecutiva fruta_da_maior_sequencia;
  fruta_da_maior_sequencia.tamanho_da_sequencia = 0;

  for (int i = 1; i < numero_de_vendas; i++) {
    if (vendas[i] == vendas[i - 1]) {
      tamanho_da_sequencia_atual++;
      if (tamanho_da_sequencia_atual >
          fruta_da_maior_sequencia.tamanho_da_sequencia) {
        fruta_da_maior_sequencia.salada = vendas[i];
        fruta_da_maior_sequencia.tamanho_da_sequencia =
            tamanho_da_sequencia_atual;
      }
    } else {
      tamanho_da_sequencia_atual = 1;
    }
  }
  return fruta_da_maior_sequencia;
}

struct contador_de_saladas contar_vendas(int vendas[], int numero_de_vendas) {
  /*
   * Conta a quantidade de vendas das frutas
   *
   * Retorna um struct com o contador de cada salada
   */
  struct contador_de_saladas contador = {0, 0, 0};
  for (int i = 0; i < numero_de_vendas; i++)
    switch (vendas[i]) {
    case 5:
      contador.salada5++;
      break;
    case 7:
      contador.salada7++;
      break;
    case 10:
      contador.salada10++;
      break;
    }
  return contador;
}

int main() {
  // Declaracao de variaveis
  int *vendas, numero_de_vendas;
  struct contador_de_saladas contagem;
  struct maior_sequencia_consecutiva fruta_da_maior_sequencia;

  // Entrada
  do {
    scanf("%d ", &numero_de_vendas);
  } while (1 > numero_de_vendas || LIMITE_DE_VENDAS < numero_de_vendas);
  vendas = malloc(numero_de_vendas * sizeof(int));
  for (int i = 0; i < numero_de_vendas; i++)
    scanf("%d ", &vendas[i]);

  // Calculos
  contagem = contar_vendas(vendas, numero_de_vendas);
  fruta_da_maior_sequencia =
      maior_sequencia_de_vendas(vendas, numero_de_vendas);

  // Saida
  printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 "
         "reais\n",
         contagem.salada5, contagem.salada7, contagem.salada10);
  printf("James vendeu %d saladas de %d reais consecutivamente\n",
         fruta_da_maior_sequencia.tamanho_da_sequencia,
         fruta_da_maior_sequencia.salada);

  // Liberar memoria e fim do programa
  free(vendas);
  return 0;
}
