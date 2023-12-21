#include "grafo.h"
#include <stdio.h>

#define ADICIONAR_VERTICE 1
#define ADICIONAR_ARESTA 2
#define REMOVER_ARESTA 3
#define VERIFICAR_CAMINHO 4
#define GERAR_CAMINHO 5
#define REDE_DE_AJACENCIA 6

int main() {
  int comando = 0, vetice_u = 0, vertice_v = 0;
  grafo conexoes = novo_grafo();
  while (scanf("%d ", &comando) && (comando > 0 && comando < 7)) {
    switch (comando) {
    case ADICIONAR_VERTICE:
      scanf("%d ", &vetice_u);
      adiciona_vertice(conexoes, vetice_u);
      break;
    case ADICIONAR_ARESTA:
      scanf("%d %d ", &vetice_u, &vertice_v);
      insere_aresta(conexoes, vetice_u, vertice_v);
      break;
    case REMOVER_ARESTA:
      scanf("%d %d ", &vetice_u, &vertice_v);
      remove_aresta(conexoes, vetice_u, vertice_v);
      break;
    case VERIFICAR_CAMINHO:
      scanf("%d %d ", &vetice_u, &vertice_v);
      imprime_se_tem_arestas(conexoes, vetice_u, vertice_v);
      break;
    case GERAR_CAMINHO:
      scanf("%d %d ", &vetice_u, &vertice_v);
      imprimir_rota(conexoes, vetice_u, vertice_v);
      break;
    case REDE_DE_AJACENCIA:
      imprimir_conexoes(conexoes);
      break;
    }
  }
  free_grafo(conexoes);
  return 0;
}
