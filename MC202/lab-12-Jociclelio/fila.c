#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Aloca uma noma fila na memoria
 */
fila nova_fila(int tamanho) {
  fila nova_fila = malloc(sizeof(struct estutura_fila));
  nova_fila->pecas = malloc(tamanho * sizeof(int));
  nova_fila->tamanho_total = tamanho;
  nova_fila->tamanho_usado = 0;
  nova_fila->inicio = 0;
  nova_fila->fim = 0;
  return nova_fila;
}

/*
 * Desaloca uma fila da memoria
 */
void free_fila(fila esse) {
  free(esse->pecas);
  free(esse);
}

/*
 * Adiciona um valor no final da fila
 */
void enfileira(fila esse, int esse_item) {
  esse->pecas[esse->fim] = esse_item;
  esse->fim = (esse->fim + 1) % esse->tamanho_total;
  esse->tamanho_usado++;
}

/*
 * remove um valor da fila e retorna esse valor
 */
int desemfileira(fila esse) {
  int esse_item = esse->pecas[esse->inicio];
  esse->inicio = (esse->inicio + 1) % esse->tamanho_total;
  esse->tamanho_usado--;
  return esse_item;
}
