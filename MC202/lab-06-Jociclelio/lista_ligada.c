#include "./lista_ligada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Aloca uma nova lista
 * e retorna o um ponteiro para ela
 */
lista nova_lista() {
  lista nova_lista = malloc(sizeof(struct lista_ligada));
  nova_lista->inicio = NULL;
  nova_lista->inserir = NULL;
  nova_lista->fim = NULL;
  return nova_lista;
}

/*
 * Desaloca um no da memoria
 */
void free_no(no esse_no) {
  free(esse_no->livro);
  free(esse_no);
}

/*
 * Desaloca no atual e todos seus consecutivos
 *  da memoria
 */
void free_nos(no esse_no) {
  if (esse_no != NULL) {
    free_nos(esse_no->proximo);
    free_no(esse_no);
  }
}

/*
 * Desaloca toda a lista
 */
void free_lista(lista esse) {
  free_nos(esse->inicio);
  free(esse);
}

/*
 * Adiciona um livro a lista
 */
void adicionar_elemento(lista esse, char *livro, int livro_tamanho) {
  /* Cria o novo no e copia o livro */
  no novo = malloc(sizeof(struct no_lista_ligada));
  novo->livro = malloc(livro_tamanho);
  strcpy(novo->livro, livro);

  if (!esse->inserir) {
    /* Insere no inicio da lista */
    novo->proximo = esse->inicio;

    /* Atualiza o ponteiro do no inicio */
    esse->inicio = novo;

  } else {
    /* Adiciona na frente do no inserir */
    no proximo = esse->inserir->proximo;
    esse->inserir->proximo = novo;
    novo->proximo = proximo;

    /* Verifica se a insercao foi no final da lista */
    if (novo->proximo == NULL)
      /* Atualiza a o ponteiro do final */
      esse->fim = novo;
  }

  /* Atualiza o ponteiro do inserir */
  esse->inserir = novo;
}

/*
 * Remove um livro da lista
 */
void remover_elemento(lista esse, char *livro) {
  no apagar, no_atual;
  /* Verifica deve ser removido o primeiro elemento */

  if (!strcmp(esse->inicio->livro, livro)) {
    /* Remove o primeiro elemento */
    apagar = esse->inicio;
    esse->inicio = esse->inicio->proximo;
    no_atual = NULL;

  } else {
    /* Procura o no a ser removido na lista */
    for (no_atual = esse->inicio;
         no_atual->proximo != NULL && strcmp(no_atual->proximo->livro, livro);
         no_atual = no_atual->proximo)
      ;
    /* Remove o no_atual->proximo */
    apagar = no_atual->proximo;
    no_atual->proximo = no_atual->proximo->proximo;
  }

  /*
   * Verifica se esse no a ser apagado
   * eh o no do fim
   */
  if (apagar->proximo == NULL)
    /* Atualiza o no do fim */
    esse->fim = no_atual;

  /*
   * Verifica se esse no a ser apagado
   * eh o no_inserir
   */
  if (apagar == esse->inserir)
    /* volta o no de inseir um no */
    esse->inserir = no_atual;

  /* Desaloca o no */
  free_no(apagar);
}

/*
 * Define o local para inserir no inicio da lista
 */
void mover_inserir_inicio(lista esse) { esse->inserir = NULL; }

/*
 * Define o local para inserir no final da lista
 */
void mover_inserir_fim(lista esse) { esse->inserir = esse->fim; }

/*
 * Imprimi um no e seus consecutivos
 */
void imprimir_nos(no esse_no) {
  if (esse_no->proximo != NULL) {
    printf("%s, ", esse_no->livro);
    imprimir_nos(esse_no->proximo);

  } else {
    printf("%s\n", esse_no->livro);
  }
}

/*
 * Imprimi a lista
 */
void imprimir(lista esse) { imprimir_nos(esse->inicio); }
