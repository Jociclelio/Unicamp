#include "arvore_de_busca_binaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Cria uma nova arvore_binaria e coloca o valor na raiz
 */
arvore_binaria nova_arvore_binaria(char *chave, char *dado,
                                   arvore_binaria esquerda,
                                   arvore_binaria direita, enum cor cor) {
  arvore_binaria nova_arvore = malloc(sizeof(struct estrutura_arvore_binaria));
  strcpy(nova_arvore->chave, chave);
  strcpy(nova_arvore->dado, dado);
  nova_arvore->esquerda = esquerda;
  nova_arvore->direita = direita;
  nova_arvore->cor = cor;
  return nova_arvore;
}

/*
 * Desaloca a arvore_binaria da memoria
 */
void free_arvore_binaria(arvore_binaria raiz_arvore) {
  if (raiz_arvore != NULL) {
    free_arvore_binaria(raiz_arvore->esquerda);
    free_arvore_binaria(raiz_arvore->direita);
    free(raiz_arvore);
  }
}

/*
 * Imprimi a arvore de simbolos
 */
void imprimir_arvore_de_simbolos(arvore_binaria esse) {
  if (esse != NULL) {
    imprimir_arvore_de_simbolos(esse->esquerda);
    printf("%s %s\n", esse->chave, esse->dado);
    imprimir_arvore_de_simbolos(esse->direita);
  }
}

/*
 * Retorna se um no eh VERMELHO ou nao
 */
int eh_vermelho(arvore_binaria esse) {
  if (esse == NULL)
    return 0;
  return esse->cor == VERMELHO;
}

/*
 * Retorna se um no eh PRETO ou nao
 */
int eh_preto(arvore_binaria esse) {
  if (esse == NULL)
    return 1;
  return esse->cor == PRETO;
}

/*
 * Executa uma rotacao para esquerda no no
 */
arvore_binaria rotaciona_para_esquerda(arvore_binaria esse) {
  arvore_binaria nova_raiz = esse->direita;
  esse->direita = nova_raiz->esquerda;
  nova_raiz->esquerda = esse;
  nova_raiz->cor = esse->cor;
  esse->cor = VERMELHO;
  return nova_raiz;
}

/*
 * Executa uma rotacao para direita no no
 */
arvore_binaria rotaciona_para_direita(arvore_binaria esse) {
  arvore_binaria nova_raiz = esse->esquerda;
  esse->esquerda = nova_raiz->direita;
  nova_raiz->direita = esse;
  nova_raiz->cor = esse->cor;
  esse->cor = VERMELHO;
  return nova_raiz;
}

/*
 * Sobeo a carateristica vermelho dos filhos para o pai
 */
void sobe_vermelho(arvore_binaria esse) {
  esse->cor = VERMELHO;
  esse->esquerda->cor = PRETO;
  esse->direita->cor = PRETO;
}

/*
 * Inseri na arvore de simbolos um novo simbolo
 */
arvore_binaria inserir(arvore_binaria esse, char *chave, char *dado) {
  if (esse == NULL)
    return nova_arvore_binaria(chave, dado, NULL, NULL, VERMELHO);

  if (strcmp(chave, esse->chave) < 0)
    esse->esquerda = inserir(esse->esquerda, chave, dado);
  else
    esse->direita = inserir(esse->direita, chave, dado);

  if (eh_vermelho(esse->direita) && eh_preto(esse->esquerda))
    esse = rotaciona_para_esquerda(esse);
  if (eh_vermelho(esse->esquerda) && eh_vermelho(esse->esquerda->esquerda))
    esse = rotaciona_para_direita(esse);
  if (eh_vermelho(esse->esquerda) && eh_vermelho(esse->direita))
    sobe_vermelho(esse);

  return esse;
}

/*
 * Busca na arvore de simbolos e retorna o no
 */
arvore_binaria buscar(arvore_binaria esse, char *chave) {
  int comparacao;
  while (esse != NULL) {
    comparacao = strcmp(esse->chave, chave);
    if (!comparacao)
      break;
    if (comparacao > 0)
      esse = esse->esquerda;
    else
      esse = esse->direita;
  }
  return esse;
}

/*
 * Busca na arvore de simbolos e retorna o dado
 */
char *buscar_simbolo(arvore_binaria esse, char *chave) {
  arvore_binaria busca = buscar(esse, chave);
  return busca != NULL ? busca->dado : NULL;
}
