#include "./batmemoria_virtual.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Cria uma nova batmemoria virtual
 */
batmemoria nova_memoria(int tamanho_inicial) {
  /* Aloca espaco para struct */
  batmemoria nova = malloc(sizeof(struct batmemoria_virtual));

  /* Cria o vetor da memoria */
  nova->memoria = novo_vetor(tamanho_inicial);

  /* Cria o vetor do indice */
  nova->indices = novo_vetor(tamanho_inicial);

  /* Adicona o primeiro indice representando o inicio do vetor */
  adicionar_elemento(nova->indices, 0);

  /* Adiciona o ultimo idice representando o fim do vetor */
  adicionar_elemento(nova->indices, nova->memoria->tamanho_alocado);

  /* inica valores iniciais */
  nova->tamanho_minimo = tamanho_inicial;
  nova->tamanho_usado = 0;

  return nova;
}

/*
 * Desaloca um vetor na batmemoria
 */
void free_batmemoria(batmemoria esse) {
  /* Libera o vetor de memoria virutal */
  free_vetor(esse->memoria);

  /* Libera o vetor de indices */
  free_vetor(esse->indices);

  /* Libera a struct batmemoria_virtual */
  free(esse);
}

/*
 * Muda o tamanho da batmemoria
 */
void mudar_tamanho_da_memoria(batmemoria esse, int novo_tamanho) {
  /* Remove a referencia anterior do vetor */
  remover_elemento(esse->indices, esse->memoria->tamanho_alocado);

  /* Muda o tamanho da memoria */
  mudar_tamanho_vetor(esse->memoria, novo_tamanho);

  /* Adicona a referencia do novo tamanho na memoria */
  adicionar_elemento(esse->indices, esse->memoria->tamanho_alocado);
}

/*
 * Aloca espaco para um vetor na batmemoria
 */
batedereco bat_alocar(batmemoria esse, int tamanho, int indice_inicial) {
  int inicio_vazio = 0, fim_ocupado = 0;

  /* Verifica se tem que testar somente se ha espaco no final */
  if (indice_inicial < 0) {
    /* Ajusta para testar o final */
    indice_inicial = esse->indices->index - 2;
    fim_ocupado = esse->indices->dados[indice_inicial];
  }

  /* Verifica se ha espaco entre dois vetores virutais */

  for (int i = indice_inicial; i + 1 < esse->indices->index; i++) {
    /* i==0 testa se tem espaco no inidio da memoria */
    if (i > 0)
      inicio_vazio =
          fim_ocupado + esse->memoria->dados[esse->indices->dados[i]] + 1;
    fim_ocupado = esse->indices->dados[i + 1];

    if ((fim_ocupado - inicio_vazio) > tamanho) {
      /* Adicona o indice no vetor de indices */
      adicionar_elemento(esse->indices, inicio_vazio);

      /* Coloca o valor do tamanho do vetor virutal na batmemoria */
      esse->memoria->dados[inicio_vazio] = tamanho;

      /* Atualiza a quantidade usada */
      esse->tamanho_usado += tamanho + 1;

      /* Retorna endereco alocado */
      return inicio_vazio;
    }
  }

  /*
   * -> Nao foi possivel colocar o vetor na memoria virutal
   */

  /* dobra o tamanho da memoria virutal */
  mudar_tamanho_da_memoria(esse, esse->memoria->tamanho_alocado * 2);

  /*
   * Chama bat_alocar novamente
   * testando somente se há como alocar no final
   * pois ja foi testado os espacos entre os vetores
   */
  return bat_alocar(esse, tamanho, -1);
}

/*
 * Dar free em um vetor na batmemoria
 */
void bat_free(batmemoria esse, batedereco endereco) {
  /* Diminui o tamanho usado pelo tamanho do vetor */
  esse->tamanho_usado -= esse->memoria->dados[endereco] + 1;

  /* Remove a referencia do vetor do indice */
  remover_elemento(esse->indices, endereco);

  /* Verifica se a memoria alocada tem que diminuir */
  if (((esse->indices->dados[esse->indices->index - 2] +
        esse->memoria->dados[esse->indices->dados[esse->indices->index - 2]]) <
       esse->memoria->tamanho_alocado / 4) &&
      esse->memoria->tamanho_alocado / 4 >= esse->tamanho_minimo)
    mudar_tamanho_da_memoria(esse, esse->memoria->tamanho_alocado / 2);
}

/*
 * Recebe valores de um vetor do stdin e guarda na batmemoria
 */
void bat_amarzenar_de_stdin(batmemoria esse, int tamanho) {
  /* Aloca espaco na memoria */
  batedereco endereco = bat_alocar(esse, tamanho, 0);

  /* Recebe valores do stdin */
  for (int i = 1; i <= tamanho; i++)
    scanf("%d ", &esse->memoria->dados[endereco + i]);
  printf("%d\n", endereco);
}

/*
 * Mostra os valores de um vetor na batmemoria
 */
void bat_print(batmemoria esse, batedereco endereco) {
  for (int i = 1; i <= esse->memoria->dados[endereco]; i++) {
    printf("%d ", esse->memoria->dados[endereco + i]);
  }
  printf("\n");
}

/*
 * Mosta o uso da batmemoria no stdout
 */
void bat_uso(batmemoria esse) {
  printf("%d de %d\n", esse->tamanho_usado, esse->memoria->tamanho_alocado);
}
