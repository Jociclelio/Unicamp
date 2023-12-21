#include "operario.h"
#include <stdlib.h>

/*
 * Aloca um novo operario na memoria
 */
operario novo_operario() {
  operario novo = malloc(sizeof(struct estutura_operario));
  novo->mao = NULL;
  return novo;
}

/*
 * Desaloca um operario da memoria
 */
void free_operario(operario esse) { free(esse); }

/*
 * Retorna 1 se um operario esta segurando uma peca
 */
int esta_segurando_peca(operario esse) { return esse->mao ? 1 : 0; }

int trabalhar_na_peca(operario esse) {
  if (esta_segurando_peca(esse) && esse->mao->tempo_etapa) {
    esse->mao->tempo_etapa--;
    return 0;
  }
  return 1;
}

/*
 * Retorna 1 se o operario estiver ociosso
 */
int esta_ociosso(operario esse) { return esse->mao ? 0 : 1; }

/*
 * Faz o operario segurar a peca passada por parametro
 */
void segurar_peca(operario esse, peca esse_peca) { esse->mao = esse_peca; }

/*
 * Larga a peca atual e retona a mesma
 */
peca largar_peca(operario esse) {
  peca enviar = esse->mao;
  esse->mao = NULL;
  return enviar;
}
