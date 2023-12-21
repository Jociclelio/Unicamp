#include "arvore_expressoes.h"
#include "otimizador_de_expressoes.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Ler e retorna caractere do stdin mantendo ele no stdin
 * caso o caractere seja "\n" consome o mesmo do stin
 */
char ver_stdin() {
  char caractere = getchar();
  if (caractere != '\n')
    ungetc(caractere, stdin);
  return caractere;
}

/*
 * Constroi uma nova arvore arvore binaria de expressoes
 * lendo as entradas do stdin
 */
arvore_binaria nova_arvore_expressoes_recursiva(arvore_binaria arvore_raiz) {
  if (eh_variavel_ou_numero(ver_stdin())) {
    if (!arvore_raiz)
      arvore_raiz = nova_arvore_binaria(getchar(), NULL, NULL);
    else
      arvore_raiz = nova_arvore_binaria(getchar(), arvore_raiz,
                                        nova_arvore_expressoes_recursiva(NULL));
    return nova_arvore_expressoes_recursiva(arvore_raiz);
  }
  return arvore_raiz;
}

/*
 * Constroi uma nova arvore arvore binaria de expressoes
 * lendo as entradas do stdin, contudo nao requer parâmetro
 */
arvore_binaria nova_arvore_expressoes_do_stdin() {
  return nova_arvore_expressoes_recursiva(NULL);
}

/*
 * Imprime uma arvore de expressoes
 */
void imprimir_arvore_expressoes_recursiva(arvore_binaria arvore) {
  if (arvore != NULL) {
    if (arvore->esquerda != NULL)
      printf("(");
    imprimir_arvore_expressoes_recursiva(arvore->esquerda);
    eh_operador(arvore->dado) ? printf(" %c ", arvore->dado)
                              : printf("%c", arvore->dado);
    imprimir_arvore_expressoes_recursiva(arvore->direita);
    if (arvore->direita != NULL)
      printf(")");
  }
}

/*
 * Imprime uma arvore de expressoes
 * e uma quebra de linha
 */
void imprimir_arvore_expressoes(arvore_binaria arvore) {
  imprimir_arvore_expressoes_recursiva(arvore);
  printf("\n");
}
