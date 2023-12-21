#include "grafo.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_ALOCADO_INICIAL 28

/*
 * Aloca um novo grafo na memoria
 */
grafo novo_grafo() {
  grafo novo = malloc(sizeof(struct estrurura_grafo));
  novo->tamanho_usado = 0;
  novo->tamanho_alocado = TAMANHO_ALOCADO_INICIAL;
  novo->adjacencia = malloc(TAMANHO_ALOCADO_INICIAL * sizeof(no));
  for (int i = 0; i < TAMANHO_ALOCADO_INICIAL; i++)
    novo->adjacencia[i] = NULL;
  return novo;
}

/*
 * Desaloca um grafo da memoria
 */
void free_grafo(grafo esse) {
  for (int i = 1; i < esse->tamanho_alocado; i++)
    free_lista(esse->adjacencia[i]);
  free(esse->adjacencia);
  free(esse);
}

/*
 * Muda o tamanho do vetor de adjacencia do grafo para
 * um novo tamanho
 */
void mudar_tamanho_vetor(grafo esse, int novo_tamanho) {
  /* Aloca um vetor com o novo tamanho */
  no *novo_vetor = malloc(novo_tamanho * sizeof(no));
  int menor = novo_tamanho > esse->tamanho_alocado ? esse->tamanho_alocado
                                                   : novo_tamanho;
  /* Copia a memoria para o novo vetor */
  memcpy(novo_vetor, esse->adjacencia, menor * sizeof(no));

  /* Libera a memoria do antigo vetor */
  free(esse->adjacencia);

  /* Atualiza o ponteiro para o vetor novo */
  esse->adjacencia = novo_vetor;

  /* Atualiza o tamanho_alocado para o novo tamanho*/
  esse->tamanho_alocado = novo_tamanho;
}

/*
 * Adiciona um novo vertice u no grafo
 * aumenta o tamanho do vertor de adjacencia caso necessario
 */
void adiciona_vertice(grafo esse, int vertice_u) {
  if (vertice_u > esse->tamanho_alocado - 1)
    mudar_tamanho_vetor(esse, vertice_u + 1);
  esse->tamanho_usado = vertice_u + 1;
}

/*
 * Insere uma aresta entre dois vertices u e v
 */
void insere_aresta(grafo esse, int vertice_u, int vertice_v) {
  esse->adjacencia[vertice_v] =
      insere_na_lista(esse->adjacencia[vertice_v], vertice_u);
  esse->adjacencia[vertice_u] =
      insere_na_lista(esse->adjacencia[vertice_u], vertice_v);
}

/*
 * Remove uma aresta entre dois vertices u e v
 */
void remove_aresta(grafo esse, int vertice_u, int vertice_v) {
  esse->adjacencia[vertice_u] =
      remove_da_lista(esse->adjacencia[vertice_u], vertice_v);
  esse->adjacencia[vertice_v] =
      remove_da_lista(esse->adjacencia[vertice_v], vertice_u);
}

/*
 * Verifica se tem uma aresta entre u e v
 */
int tem_aresta(grafo esse, int vertice_u, int vertice_v) {
  for (no vertice_atual = esse->adjacencia[vertice_u]; vertice_atual != NULL;
       vertice_atual = vertice_atual->proximo)
    if (vertice_atual->vertice == vertice_v)
      return 1;
  return 0;
}

/*
 * Funcao usada pela funcao existe_caminho para verificar se dois pontos sao
 * conectados diretamente ou indiretamente.
 */
int busca_recursiva(grafo esse, int *visitado, int vertice_u, int vertice_v) {
  /* Sempre existe um caminho de u para u*/
  if (vertice_u == vertice_v)
    return 1;
  /* Marca como visitado */
  visitado[vertice_u] = 1;

  /* procura na vizinhanca do vertice_u um vertice nao visitado que
   * tenha um caminho dele para o vertice_v */
  for (int vertice = 1; vertice < esse->tamanho_alocado; vertice++)
    if (tem_aresta(esse, vertice_u, vertice) && !visitado[vertice])
      if (busca_recursiva(esse, visitado, vertice, vertice_v))
        return 1;
  return 0;
}

/*
 * Verifica se existe caminho entre os vetices passados por parametro
 */
int existe_caminho(grafo esse, int vertice_u, int vertice_v) {
  int encontrou, vertice,
      *visitado = malloc(esse->tamanho_alocado * sizeof(int));
  for (vertice = 1; vertice < esse->tamanho_alocado; vertice++)
    visitado[vertice] = 0;
  encontrou = busca_recursiva(esse, visitado, vertice_u, vertice_v);
  free(visitado);
  return encontrou;
}

/*
 * Imprime se existe caminho entre dois vertices u e v
 */
void imprime_se_tem_arestas(grafo esse, int vertice_u, int vertice_v) {
  if (existe_caminho(esse, vertice_u, vertice_v))
    printf("Existe conexão entre os nós.\n");
  else
    printf("Não existe conexão entre os nós.\n");
}

void visita_recursiva(grafo esse, int *componentes, int componente,
                      int vertice_v) {
  componentes[vertice_v] = componente;
  for (no vertice_atual = esse->adjacencia[vertice_v]; vertice_atual != NULL;
       vertice_atual = vertice_atual->proximo)
    if (componentes[vertice_atual->vertice] == -1)
      visita_recursiva(esse, componentes, componente, vertice_atual->vertice);
}

/*
 * Encontra as componentes conexas de cada vertice
 * Retorna um vetor de inteiros de tamanho esse->tamanho_usado
 * onde o o indice i guarda a componente do vertice i
 * salva o numero de componentes no inteiro passado por referencia
 */
int *encontra_componentes(grafo esse, int *numero_de_componentes) {
  int componente = 0, *componentes = malloc(esse->tamanho_usado * sizeof(int));
  for (int i = 1; i < esse->tamanho_usado; i++)
    componentes[i] = -1;
  for (int i = 1; i < esse->tamanho_usado; i++)
    if (componentes[i] == -1) {
      visita_recursiva(esse, componentes, componente, i);
      componente++;
    }
  *numero_de_componentes = componente;
  return componentes;
}

/*
 * Imprimi as conexoes diretas e indiretas de cada vertice
 */
void imprimir_conexoes(grafo esse) {
  int numero_de_componentes = 0;
  int *componentes = encontra_componentes(esse, &numero_de_componentes);
  char **texto_conexoes = malloc(numero_de_componentes * sizeof(char *));
  char buffer[16] = "";
  for (int i = 0; i < numero_de_componentes; i++) {
    texto_conexoes[i] = malloc(48 * sizeof(char));
    strcpy(texto_conexoes[i], "");
  }
  for (int i = 1; i < esse->tamanho_usado; i++) {
    sprintf(buffer, " %d", i);
    strcat(texto_conexoes[componentes[i]], buffer);
  }
  for (int i = 1; i < esse->tamanho_usado; i++)
    printf("Ponto %d (Pontos diretamente ou indiretamente conectados):%s\n", i,
           texto_conexoes[componentes[i]]);
  for (int i = 0; i < numero_de_componentes; i++)
    free(texto_conexoes[i]);
  free(texto_conexoes);
  free(componentes);
}

/*
 * Exectua uma busca em largura a partir do vertice
 * Retorna um vetor de inteiros de tamanho esse->tamanho_usado
 * onde o valor do indice i corresponde ao vertice pai do vertice i
 */
int *busca_em_largura(grafo esse, int vertice) {
  int *indice_pai = malloc(esse->tamanho_usado * sizeof(int));
  int *visitado = malloc(esse->tamanho_usado * sizeof(int));
  fila fila = nova_fila(esse->tamanho_usado);
  for (int vertice = 1; vertice < esse->tamanho_usado; vertice++) {
    indice_pai[vertice] = -1;
    visitado[vertice] = 0;
  }
  enfileira(fila, vertice);
  indice_pai[vertice] = vertice;
  visitado[vertice] = 1;
  while (fila->tamanho_usado) {
    int vertice_pai = desemfileira(fila);
    for (int vertice = 1; vertice < esse->tamanho_usado; vertice++)
      if (tem_aresta(esse, vertice_pai, vertice) && !visitado[vertice]) {
        visitado[vertice] = 1;
        indice_pai[vertice] = vertice_pai;
        enfileira(fila, vertice);
      }
  }
  free_fila(fila);
  free(visitado);
  return indice_pai;
}

/*
 * Imprimi uma rota de menor caminho entre o vertices
 * passados por parametro
 */
void imprimir_rota(grafo esse, int vertice_u, int vertice_v) {
  char mensagem[256] = "", buffer[16] = "";
  int vertice_atual;
  int *pai = busca_em_largura(esse, vertice_v);
  for (vertice_atual = vertice_u;
       pai[vertice_atual] != -1 && vertice_atual != pai[vertice_atual];
       vertice_atual = pai[vertice_atual]) {
    sprintf(buffer, "%d -> ", vertice_atual);
    strcat(mensagem, buffer);
  }
  sprintf(buffer, "%d", vertice_v);
  strcat(mensagem, buffer);

  if (pai[vertice_atual] != -1)
    /* puts coloca um \n no final*/
    puts(mensagem);
  else
    printf("Não existe conexão entre os nós.\n");

  free(pai);
}
