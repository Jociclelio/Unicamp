#include "peca.h"
#define TIPO_DOS_VALORES_DA_PILHA peca

typedef struct estrutura_no_pilha *no_pilha;
typedef struct estrutura_pilha *pilha;

struct estrutura_no_pilha {
  TIPO_DOS_VALORES_DA_PILHA peca;
  no_pilha proximo;
};

struct estrutura_pilha {
  no_pilha topo;
  int tamanho_total;
  int tamanho_usado;
};

/*
 * Cria uma nova pilha
 */
pilha nova_pilha(int tamanho);

/*
 * Desaloca uma pilha
 */
void free_pilha(pilha essa);

/*
 * Retorna o tamanho disponivel de uma fila
 */
int tamanho_disponivel_pilha(pilha essa);

/*
 * Empilha um valor na pilha
 */
void empilhar(pilha essa, TIPO_DOS_VALORES_DA_PILHA essa_peca);

/*
 * Desempilha um valor da pilha
 */
TIPO_DOS_VALORES_DA_PILHA desempilhar(pilha essa);
