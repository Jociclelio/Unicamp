#include "registro.h"
#include <stdio.h>
#include <stdlib.h>

registro_etapa novo_registro_etapa() {
  registro_etapa novo = malloc(sizeof(struct estrutura_registro_etapa));
  novo->saida = 0;
  novo->entrada = 0;
  return novo;
}

void resetar_registro_etapa(registro_etapa esse) {
  esse->entrada = 0;
  esse->saida = 0;
}

void resetar_registro_etapas(registro esse) {
  resetar_registro_etapa(esse->classificacao);
  resetar_registro_etapa(esse->embalacao);
}

registro novo_registro() {
  registro novo = malloc(sizeof(struct estrutura_registro));
  novo->classificacao = novo_registro_etapa();
  novo->embalacao = novo_registro_etapa();
  novo->total_entrada = 0;
  novo->total_saida = 0;
  novo->atrazo = 0;
  resetar_registro_etapas(novo);
  return novo;
}

void free_registro_etapa(registro_etapa esse) { free(esse); }

void free_registro(registro esse) {
  free_registro_etapa(esse->classificacao);
  free_registro_etapa(esse->embalacao);
  free(esse);
}

void imprimir_relatorio_minuto(registro esse, int minuto) {
  printf("Min. %d: Classificação (+%d,-%d) | Embalagem (+%d,-%d).\n", minuto,
         esse->classificacao->entrada, esse->classificacao->saida,
         esse->embalacao->entrada, esse->embalacao->saida);
  resetar_registro_etapas(esse);
}

void imprimir_relatorio_atrazo(registro esse) {
  printf("Tempo atraso: %d.\n", esse->atrazo);
}
