#include "lista.h"
typedef struct estrurura_grafo *grafo;

struct estrurura_grafo {
  no *adjacencia;
  int tamanho_usado;
  int tamanho_alocado;
};

/*
 * Aloca um novo grafo na memoria
 */
grafo novo_grafo();

/*
 * Desaloca um grafo da memoria
 */
void free_grafo(grafo esse);

/*
 * Adiciona um novo vertice u no grafo
 * aumenta o tamanho do vertor de adjacencia caso necessario
 */
void adiciona_vertice(grafo esse, int u);

/*
 * Insere uma aresta entre dois vertices u e v
 */
void insere_aresta(grafo esse, int u, int v);

/*
 * Remove uma aresta entre dois vertices u e v
 */
void remove_aresta(grafo esse, int u, int v);

/*
 * Imprime se existe caminho entre dois vertices u e v
 */
void imprime_se_tem_arestas(grafo esse, int u, int v);

/*
 * Imprimi a menor rota entre o vertice u e v
 */
void imprimir_rota(grafo esse, int u, int v);

/*
 * Imprimi as conexoes de cada vertice
 */
void imprimir_conexoes(grafo esse);
