#include "otimizador_de_expressoes.h"
#include <stdlib.h>

#define NUMERO_DE_OPERADORES 8

/*
 * Retorna 1 se um caractere eh um operador
 */
int eh_operador(char caractere) {
  char operadores[NUMERO_DE_OPERADORES] = {'&', '|', '<', '>',
                                           '{', '}', '!', '='};
  for (int i = 0; i < NUMERO_DE_OPERADORES; i++)
    if (operadores[i] == caractere)
      return 1;
  return 0;
}

/*
 * Retorna 1 se o caractere e um numero
 */
int eh_numero(char caractere) {
  return ('0' <= caractere) && (caractere <= '9');
}

/*
 * Retorna 1 se o caractere eh uma variavel
 */
int eh_variavel(char caractere) {
  return ('a' <= caractere) && (caractere <= 'z');
}

/*
 * Retorna 1 se o caractere eh um numero ou uma variavel
 */
int eh_variavel_ou_numero(char caractere) {
  return (eh_numero(caractere) || eh_variavel(caractere));
}

/*
 * Rerona 1 se o caractere eh True ou False
 */
int eh_true_ou_false(char caractere) {
  return (caractere == 'T') || (caractere == 'F');
}

/*
 * otimiza uma expressao
 */
void otimizar(arvore_binaria arvore, char dado) {
  arvore->dado = dado;
  free_arvore_binaria(arvore->esquerda);
  free_arvore_binaria(arvore->direita);
  arvore->esquerda = NULL;
  arvore->direita = NULL;
}

/*
 * Otimiza de acordo com uma condicional passada por parametro
 */
void otimizar_condicional(arvore_binaria arvore, int comparacao) {
  comparacao ? otimizar(arvore, 'T') : otimizar(arvore, 'F');
}

/*
 * Otimiza expressao numerica
 * do tipo <numero> <operador> <numero>
 */
void otimizar_expressao_numerica(arvore_binaria arvore) {
  switch (arvore->dado) {
  case '=':
    otimizar_condicional(arvore,
                         arvore->esquerda->dado == arvore->direita->dado);
    break;
  case '!':
    otimizar_condicional(arvore,
                         arvore->esquerda->dado != arvore->direita->dado);
    break;
  case '>':
    otimizar_condicional(arvore,
                         arvore->esquerda->dado > arvore->direita->dado);
    break;
  case '<':
    otimizar_condicional(arvore,
                         arvore->esquerda->dado < arvore->direita->dado);
    break;
  case '}':
    otimizar_condicional(arvore,
                         arvore->esquerda->dado >= arvore->direita->dado);
    break;
  case '{':
    otimizar_condicional(arvore,
                         arvore->esquerda->dado <= arvore->direita->dado);
    break;
  }
}

/*
 * Otimiza expressao logica do tipo
 * <T ou F> <operador> <expressao>
 */
void otimizar_expressao_logica(arvore_binaria arvore) {
  if (arvore->dado == '|' &&
      (arvore->esquerda->dado == 'T' || arvore->direita->dado == 'T')) {
    otimizar(arvore, 'T');
  } else if (arvore->dado == '&' &&
             (arvore->esquerda->dado == 'F' || arvore->direita->dado == 'F')) {
    otimizar(arvore, 'F');
  }
}

/*
 * otimizar expressoes pre determinadas pelo conjunto
 */
void otimizar_expressao_pre_determinada(arvore_binaria arvore) {
  if (((arvore->dado == '}' && arvore->direita->dado == '0') ||
       (arvore->dado == '{' && arvore->esquerda->dado == '0')) ||
      ((arvore->dado == '{' && arvore->direita->dado == '9') ||
       (arvore->dado == '}' && arvore->esquerda->dado == '9'))) {
    otimizar(arvore, 'T');
  } else if (((arvore->dado == '>' && arvore->direita->dado == '9') ||
              (arvore->dado == '<' && arvore->esquerda->dado == '9')) ||
             ((arvore->dado == '<' && arvore->direita->dado == '0') ||
              (arvore->dado == '>' && arvore->esquerda->dado == '0'))) {
    otimizar(arvore, 'F');
  }
}

/*
 * Otimiza expressao com base a situacao
 */
void otimizar_expressao(arvore_binaria arvore) {
  // Verifica se a expressao eh otimizavel
  if (!(eh_operador(arvore->esquerda->dado) &&
        eh_operador(arvore->direita->dado))) {
    // Verifica o casos de otimizacao
    if (arvore->esquerda->dado == arvore->direita->dado) {
      otimizar_condicional(arvore, arvore->dado == '=' || arvore->dado == '{' ||
                                       arvore->dado == '}');
    } else if (eh_numero(arvore->esquerda->dado) &&
               eh_numero(arvore->direita->dado)) {
      otimizar_expressao_numerica(arvore);
    } else if (eh_true_ou_false(arvore->esquerda->dado) |
               eh_true_ou_false(arvore->direita->dado)) {
      otimizar_expressao_logica(arvore);

    } else if (eh_variavel_ou_numero(arvore->esquerda->dado) &&
               eh_variavel_ou_numero(arvore->direita->dado)) {
      otimizar_expressao_pre_determinada(arvore);
    }
  }
}

/*
 * Otimiza uma arvore de expressoes
 */
void otimizar_arvore_expressoes(arvore_binaria arvore) {
  if (arvore != NULL && arvore->direita != NULL && arvore->esquerda != NULL) {
    otimizar_arvore_expressoes(arvore->esquerda);
    otimizar_arvore_expressoes(arvore->direita);
    otimizar_expressao(arvore);
  }
}
