#include "fila_de_pedidos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAI(i) ((i - 1) / 2)
#define FILHO_ESQUERDO(i) (2 * i + 1)
#define FILHO_DIREITO(i) (2 * i + 2)

pedido novo_pedido(char *prato, int prato_tamanho, int id, int valor) {
  pedido novo = malloc(sizeof(struct estrutura_pedido));
  novo->prato = malloc(prato_tamanho * sizeof(char));
  strcpy(novo->prato, prato);
  novo->id = id;
  novo->valor = valor;
  return novo;
}

fila_de_pedidos nova_fila_de_pedidos(sobrevivente *sobreviventes,
                                     int quantidade_de_sobreviventes) {
  fila_de_pedidos novo = malloc(sizeof(struct estrutura_fila_de_pedidos));
  novo->vetor_heap = malloc(quantidade_de_sobreviventes * sizeof(pedido));
  novo->numero_usado = 0;
  novo->tamanho_alocado = quantidade_de_sobreviventes;
  novo->sobreviventes = sobreviventes;
  return novo;
}

void free_pedido(pedido esse) {
  free(esse->prato);
  free(esse);
}

void free_fila_de_pedidos(fila_de_pedidos esse) {
  free(esse->vetor_heap);
  for (int i = 0; i < esse->numero_usado; i++)
    free_pedido(esse->vetor_heap[i]);
  free(esse);
}

void troca_posicao_no_vetor_heap(fila_de_pedidos esse, int indice_item_a,
                                 int indice_item_b) {
  pedido t = esse->vetor_heap[indice_item_a];
  esse->vetor_heap[indice_item_a] = esse->vetor_heap[indice_item_b];
  esse->vetor_heap[indice_item_b] = t;
  esse->sobreviventes[esse->vetor_heap[indice_item_a]->id]->indice_prato =
      indice_item_a;
  esse->sobreviventes[esse->vetor_heap[indice_item_b]->id]->indice_prato =
      indice_item_b;
}

void sobe_no_heap(fila_de_pedidos esse, int i) {
  if (i > 0 && esse->vetor_heap[PAI(i)]->valor < esse->vetor_heap[i]->valor) {
    troca_posicao_no_vetor_heap(esse, i, PAI(i));
    sobe_no_heap(esse, PAI(i));
  }
}

void desce_no_heap(fila_de_pedidos esse, int k) {
  int maior_filho;
  if (FILHO_ESQUERDO(k) < esse->numero_usado) {
    maior_filho = FILHO_ESQUERDO(k);
    if (FILHO_DIREITO(k) < esse->numero_usado &&
        esse->vetor_heap[FILHO_ESQUERDO(k)]->valor <
            esse->vetor_heap[FILHO_DIREITO(k)]->valor)
      maior_filho = FILHO_DIREITO(k);
    if (esse->vetor_heap[k]->valor < esse->vetor_heap[maior_filho]->valor) {
      troca_posicao_no_vetor_heap(esse, k, maior_filho);
      desce_no_heap(esse, maior_filho);
    }
  }
}

void inserir_heap(fila_de_pedidos esse, pedido item) {
  esse->vetor_heap[esse->numero_usado] = item;
  esse->sobreviventes[item->id]->indice_prato = esse->numero_usado;
  esse->numero_usado++;
  sobe_no_heap(esse, esse->numero_usado - 1);
}

void inserir_novo_pedido(fila_de_pedidos esse, int id, char *prato,
                         int prato_tamanho) {
  inserir_heap(
      esse, novo_pedido(prato, prato_tamanho, id,
                        esse->sobreviventes[id]->numero_de_dias_sobrevividos));
}

pedido extrair_o_maximo(fila_de_pedidos esse) {
  pedido item = esse->vetor_heap[0];
  troca_posicao_no_vetor_heap(esse, 0, esse->numero_usado - 1);
  esse->numero_usado--;
  desce_no_heap(esse, 0);
  return item;
}

void mudar_prioridade_de_pedido(fila_de_pedidos esse, int id, int valor) {
  int i = esse->sobreviventes[id]->indice_prato;
  valor += esse->vetor_heap[i]->valor;
  if (esse->vetor_heap[i]->valor < valor) {
    esse->vetor_heap[i]->valor = valor;
    sobe_no_heap(esse, i);
  } else {
    esse->vetor_heap[i]->valor = valor;
    desce_no_heap(esse, i);
  }
}
