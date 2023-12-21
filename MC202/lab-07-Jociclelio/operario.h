#ifndef OPERARIO_H
#define OPERARIO_H

#include "peca.h"

typedef struct estutura_operario *operario;
struct estutura_operario {
  peca mao;
};

/*
 * Aloca um novo operario na memoria
 */
operario novo_operario();

/*
 * Desaloca um operario da memoria
 */
void free_operario(operario esse);

/*
 * Retorna 1 se um operario esta segurando uma peca
 */
int esta_segurando_peca(operario esse);

/*
 * Tenta trabalhar na peca
 * Retorna 1 se nao consegiu
 */
int trabalhar_na_peca(operario esse);

/*
 * Retorna 1 se o operario estiver ociosso
 */
int esta_ociosso(operario esse);

/*
 * Faz o operario segurar a peca passada por parametro
 */
void segurar_peca(operario esse, peca esse_peca);

/*
 * Larga a peca atual e retona a mesma
 */
peca largar_peca(operario esse);

#endif
