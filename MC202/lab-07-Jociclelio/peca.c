#include "peca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

peca nova_peca(char *tamanho, int tipo) {
  peca nova_peca = malloc(sizeof(struct estutura_peca));
  strcpy(nova_peca->tamanho, tamanho);
  nova_peca->tipo = tipo;
  nova_peca->tempo_etapa = 0;
  return nova_peca;
}

peca ler_peca_do_stdin() {
  char tamanho[32];
  int tipo = 0;
  scanf("%s %d ", tamanho, &tipo);
  return nova_peca(tamanho, tipo);
}

int tempo_clasificacao(peca essa) {
  int tempo = 0;
  if (!strcmp(essa->tamanho, "pequena"))
    tempo = 1;
  else if (!strcmp(essa->tamanho, "media"))
    tempo = 2;
  else if (!strcmp(essa->tamanho, "grande"))
    tempo = 3;
  return tempo;
}

int tempo_embalacao(peca essa) {
  int tempo_para_classificar = tempo_clasificacao(essa);
  int tmp = essa->tipo;
  if (tempo_para_classificar > 2)
    tmp--;
  tmp--;
  return tempo_para_classificar + tmp;
}

void inicializar_tempo_classificacao(peca essa) {
  essa->tempo_etapa = tempo_clasificacao(essa);
}

void inicializar_tempo_embalacao(peca essa) {
  essa->tempo_etapa = tempo_embalacao(essa);
}

void free_peca(peca essa) { free(essa); }
