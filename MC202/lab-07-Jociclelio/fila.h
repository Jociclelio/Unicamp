#include "peca.h"

#define TIPO_DOS_VALORES_DA_FILA peca

typedef struct estutura_fila *fila;
struct estutura_fila {
  TIPO_DOS_VALORES_DA_FILA *pecas;
  int inicio;
  int fim;
  int tamanho_total;
  int tamanho_usado;
};

/*
 * Cria uma nova esteira
 */
fila nova_fila(int tamanho);

/*
 * Desaloca uma esteira da memoria
 * mas nao da free nos valores de fila
 */
void free_fila(fila esse);

/*
 * Retorna o tamanho de espaco livro da esteira
 */
int tamanho_disponivel_fila(fila esse);

/*
 * Adiciona um valor no final da esteira
 */
void enfileira(fila essa, TIPO_DOS_VALORES_DA_FILA essa_peca);

/*
 * Remove um valor do inicio da fila
 */
TIPO_DOS_VALORES_DA_FILA desemfileira(fila essa);
