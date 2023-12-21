#include "pilha.h"
#include <stdlib.h>

pilha nova_pilha(int tamanho) {
  pilha nova_pilha = malloc(sizeof(struct estrutura_pilha));
  nova_pilha->tamanho_total = tamanho;
  nova_pilha->tamanho_usado = 0;
  nova_pilha->topo = NULL;
  return nova_pilha;
}

void free_no_pilha(no_pilha esse_no) {
  if (esse_no != NULL) {
    free_no_pilha(esse_no->proximo);
    free(esse_no);
  }
}

void free_pilha(pilha esse) {
  free_no_pilha(esse->topo);
  free(esse);
}

int tamanho_disponivel_pilha(pilha esse) {
  return esse->tamanho_total - esse->tamanho_usado;
}

void empilhar(pilha esse, TIPO_DOS_VALORES_DA_PILHA dado_empilhar) {
  no_pilha novo_no_pilha = malloc(sizeof(struct estrutura_no_pilha));
  inicializar_tempo_embalacao(dado_empilhar);
  novo_no_pilha->peca = dado_empilhar;
  novo_no_pilha->proximo = esse->topo;
  esse->tamanho_usado++;
  esse->topo = novo_no_pilha;
}

TIPO_DOS_VALORES_DA_PILHA desempilhar(pilha esse) {
  no_pilha topo = esse->topo;
  TIPO_DOS_VALORES_DA_PILHA dado_desempilhar = topo->peca;
  esse->topo = esse->topo->proximo;
  esse->tamanho_usado--;
  free(topo);
  return dado_desempilhar;
}
