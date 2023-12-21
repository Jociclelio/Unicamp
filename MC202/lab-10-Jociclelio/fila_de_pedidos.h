#include "sobrevivente.h"
typedef struct estrutura_pedido *pedido;
struct estrutura_pedido {
  char *prato;
  int valor;
  int id;
};

typedef struct estrutura_fila_de_pedidos *fila_de_pedidos;
struct estrutura_fila_de_pedidos {
  sobrevivente *sobreviventes;
  pedido *vetor_heap;
  int numero_usado;
  int tamanho_alocado;
};

/*
 * Aloca uma nova fila de pedidos na memoria
 */
fila_de_pedidos nova_fila_de_pedidos(sobrevivente *sobreviventes,
                                     int quantidade_de_sobreviventes);

/*
 * Desaloca uma fila de pedidos da memoria
 */
void free_fila_de_pedidos(fila_de_pedidos esse);

/*
 * Aloca um novo pedido na memoria
 */
pedido novo_pedido(char *prato, int prato_tamanho, int id, int valor);

/*
 * Desaloca um pedido da memoria
 */
void free_pedido(pedido esse);

/*
 * Inseri um novo pedido na fila de prioridade
 */
void inserir_novo_pedido(fila_de_pedidos esse, int id, char *prato,
                         int tamanho_prato);

/*
 * Extrai o pedido de maior prioridade da fila de prioridade
 */
pedido extrair_o_maximo(fila_de_pedidos esse);

/*
 * Muda a prioridade de um pedido na fila, passado o id por parametro
 */
void mudar_prioridade_de_pedido(fila_de_pedidos esse, int id, int valor);
