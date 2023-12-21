#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

fila nova_fila(int tamanho) {
  fila nova_fila = malloc(sizeof(struct estutura_fila));
  nova_fila->pecas = malloc(tamanho * sizeof(peca));
  nova_fila->tamanho_total = tamanho;
  nova_fila->tamanho_usado = 0;
  nova_fila->inicio = 0;
  nova_fila->fim = 0;
  return nova_fila;
}

void free_fila(fila esse) {
  free(esse->pecas);
  free(esse);
}

int tamanho_disponivel_fila(fila esse) {
  return esse->tamanho_total - esse->tamanho_usado;
}

void enfileira(fila esse, TIPO_DOS_VALORES_DA_FILA essa_peca) {
  inicializar_tempo_classificacao(essa_peca);
  esse->pecas[esse->fim] = essa_peca;
  esse->fim = (esse->fim + 1) % esse->tamanho_total;
  esse->tamanho_usado++;
}

TIPO_DOS_VALORES_DA_FILA desemfileira(fila esse) {
  peca essa_peca = esse->pecas[esse->inicio];
  esse->inicio = (esse->inicio + 1) % esse->tamanho_total;
  esse->tamanho_usado--;
  return essa_peca;
}
