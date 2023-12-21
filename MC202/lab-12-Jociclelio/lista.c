#include "lista.h"
#include <stdlib.h>

/*
 * Desaloca uma lista ligada
 */
void free_lista(no esse) {
  if (esse != NULL) {
    free_lista(esse->proximo);
    free(esse);
  }
}

/*
 * Isere um no na lista e
 * retorna o ponteiro da lista completa
 */
no insere_na_lista(no esse, int vertice) {
  no novo = malloc(sizeof(struct estrurura_no));
  novo->vertice = vertice;
  novo->proximo = esse;
  return novo;
}

/*
 * Remove um item da lista ligada e
 * retorna o ponteiro da lista completa
 */
no remove_da_lista(no esse, int vertice) {
  no no_atual, apagar;
  if (esse == NULL)
    return NULL;
  else if (esse->vertice == vertice) {
    no_atual = esse->proximo;
    free(esse);
    return no_atual;
  } else {
    for (no_atual = esse->proximo; no_atual->proximo != NULL;
         no_atual = no_atual->proximo)
      if (no_atual->proximo->vertice == vertice) {
        apagar = no_atual->proximo;
        no_atual->proximo = no_atual->proximo->proximo;
        free(apagar);
        return esse;
      }
    return esse;
  }
}
