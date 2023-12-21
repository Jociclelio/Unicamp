#include "./vetor_dinamico.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*
 * Cria um novo vetor dinamico
 */
vetor novo_vetor(int tamanho) {
  vetor novo_vetor_dinamico = malloc(sizeof(struct vetor_dinamico));

  novo_vetor_dinamico->dados = malloc(tamanho * sizeof(TIPO_DOS_VALORES));
  novo_vetor_dinamico->tamanho_alocado = tamanho;
  novo_vetor_dinamico->index = 0;

  return novo_vetor_dinamico;
}

/*
 * Desaloca da memoria o vetor dinamico
 */
void free_vetor(vetor esse) {
  free(esse->dados);
  free(esse);
}

/*
 * Muda o tamanho do vetor dinamico
 */
void mudar_tamanho_vetor(vetor esse, int novo_tamanho) {
  /* Aloca um vetor com o novo tamanho */
  TIPO_DOS_VALORES *novo_vetor =
      malloc(novo_tamanho * sizeof(TIPO_DOS_VALORES));

  /* Copia a memoria para o novo vetor */
  memcpy(novo_vetor, esse->dados,
         fmin(novo_tamanho, esse->tamanho_alocado) * sizeof(TIPO_DOS_VALORES));

  /* Libera a memoria do antigo vetor */
  free(esse->dados);

  /* Atualiza o ponteiro para o vetor novo */
  esse->dados = novo_vetor;

  /* Atualiza o tamanho_alocado para o novo tamanho*/
  esse->tamanho_alocado = novo_tamanho;
}

/*
 * Executa a busca busca binaria para encontrar o indice de um valor
 */
int busca_binaria(int *dados, int inicio, int fim, int posicao_ordenada,
                  TIPO_DOS_VALORES valor) {
  int meio = (inicio + fim) / 2;
  if (inicio > fim)
    return posicao_ordenada ? inicio : -1;
  if (dados[meio] == valor)
    return meio;
  else if (dados[meio] < valor)
    return busca_binaria(dados, meio + 1, fim, posicao_ordenada, valor);
  else
    return busca_binaria(dados, inicio, meio - 1, posicao_ordenada, valor);
}

/*
 * Chama a funcao de busca binaria com os valores
 */
int busca(vetor esse, TIPO_DOS_VALORES valor) {
  return busca_binaria(esse->dados, 0, esse->index - 1, 0, valor);
}

/*
 * Busca a posicao para inserir ordenadamente
 */
int busca_posicao_ordenada(vetor esse, TIPO_DOS_VALORES valor) {
  return busca_binaria(esse->dados, 0, esse->index - 1, 1, valor);
}

/*
 * Adiciona um elemento no vetor de forma ordenada
 */
void adicionar_elemento(vetor esse, TIPO_DOS_VALORES valor) {
  int i = busca_posicao_ordenada(esse, valor);

  if (esse->index == esse->tamanho_alocado)
    mudar_tamanho_vetor(esse, esse->tamanho_alocado * 2);

  for (i = esse->index - 1; i >= 0 && esse->dados[i] > valor; i--)
    esse->dados[i + 1] = esse->dados[i];
  esse->dados[i + 1] = valor;

  esse->index++;
}

/*
 * Remove um elemento de e preenche e move o valores com indices
 * maiores para a posicao imediatamente menor
 */
void remover_elemento(vetor esse, TIPO_DOS_VALORES valor) {
  int i = busca(esse, valor);
  /*
   * Equivalente a:
   * for (; i < esse->index - 1; i++)
   *   esse->dados[i] = esse->dados[i + 1];
   */
  memcpy(&esse->dados[i], &esse->dados[i + 1],
         (esse->index - i - 1) * sizeof(TIPO_DOS_VALORES));

  esse->index--;

  if (esse->index < esse->tamanho_alocado / 4)
    mudar_tamanho_vetor(esse, esse->tamanho_alocado / 2);
}
