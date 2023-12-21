#include "arvore_expressoes.h"
#include <stdio.h>

int main() {
  int numero_de_expressoes = 0;
  scanf("%d ", &numero_de_expressoes);
  for (int i = 0; i < numero_de_expressoes; i++) {
    arvore_binaria arvore = nova_arvore_expressoes_do_stdin();
    imprimir_arvore_expressoes(arvore);
    otimizar_arvore_expressoes(arvore);
    imprimir_arvore_expressoes(arvore);
    if (i + 1 < numero_de_expressoes)
      printf("\n");
    free_arvore_binaria(arvore);
  }
  return 0;
}
