#include "arvore_binaria.h"
#include <stdio.h>
#include <stdlib.h>

arvore_binaria nova_arvore_binaria(TIPO_DOS_DADOS_ARVORE_BINARIA dado,
                                   arvore_binaria esquerda,
                                   arvore_binaria direita) {
  arvore_binaria nova_arvore = malloc(sizeof(struct estrutura_arvore_binaria));
  nova_arvore->dado = dado;
  nova_arvore->esquerda = esquerda;
  nova_arvore->direita = direita;
  return nova_arvore;
}

void free_arvore_binaria(arvore_binaria raiz_arvore) {
  if (raiz_arvore != NULL) {
    free_arvore_binaria(raiz_arvore->esquerda);
    free_arvore_binaria(raiz_arvore->direita);
    free(raiz_arvore);
  }
}
