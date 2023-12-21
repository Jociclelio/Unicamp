#include "hash.h"
#include <stdlib.h>
#include <string.h>

int hash(char *chave) {
  int numero_hash = 0;
  for (int i = 0; i < strlen(chave); i++)
    numero_hash = (265 * numero_hash + chave[i]) % MAX;
  return numero_hash;
}

hash_table novo_hash_table() {
  hash_table novo = malloc(sizeof(struct estrutura_hash_table));
  novo->vetor = malloc(MAX * sizeof(item));
  novo->vazio = malloc(sizeof(struct estrutura_item));
  novo->removido = malloc(sizeof(struct estrutura_item));
  for (int i = 0; i < MAX; i++)
    novo->vetor[i] = novo->vazio;
  return novo;
}

item novo_item(char *chave, int dado) {
  item novo = malloc(sizeof(struct estrutura_item));
  strcpy(novo->chave, chave);
  novo->dado = dado;
  return novo;
}

void free_hash_table(hash_table esse) {
  for (int i = 0; i < MAX; i++)
    if (esse->vetor[i] != esse->removido && esse->vetor[i] != esse->vazio)
      free(esse->vetor[i]);
  free(esse->vetor);
  free(esse->removido);
  free(esse->vazio);
  free(esse);
}

void inserir(hash_table esse, char *chave, int dado) {
  int hash_chave = hash(chave);
  item novo = novo_item(chave, dado);
  for (int i = 0; i < MAX; i++)
    if (esse->vetor[(hash_chave + i) % MAX] == esse->vazio ||
        esse->vetor[(hash_chave + i) % MAX] == esse->removido) {
      esse->vetor[(hash_chave + i) % MAX] = novo;
      return;
    }
}

void remover(hash_table esse, char *chave) {
  int hash_chave = hash(chave);
  for (int i = 0; i < MAX; i++)
    if ((!strcmp(esse->vetor[(hash_chave + i) % MAX]->chave, chave))) {
      free(esse->vetor[(hash_chave + i) % MAX]);
      esse->vetor[(hash_chave + i) % MAX] = esse->removido;
      return;
    }
}

int buscar(hash_table esse, char *chave) {
  int *dado_busca = dado(esse, chave);
  return dado_busca ? *dado_busca : -1;
}

int *dado(hash_table esse, char *chave) {
  int hash_chave = hash(chave);
  for (int i = 0; i < MAX && esse->vetor[(hash_chave + i) % MAX] != esse->vazio;
       i++)
    if (esse->vetor[(hash_chave + i) % MAX] != esse->removido &&
        (!strcmp(esse->vetor[(hash_chave + i) % MAX]->chave, chave)))
      return &esse->vetor[(hash_chave + i) % MAX]->dado;
  return NULL;
}
