#define TIPO_DOS_VALORES int

struct vetor_dinamico {
  TIPO_DOS_VALORES *dados;
  int index;
  int tamanho_alocado;
};
typedef struct vetor_dinamico *vetor;

/*
 * Cria um novo vetor dinamico
 */
vetor novo_vetor(int tamanho);

/*
 * Muda o tamanho do vetor dinamico
 */
void mudar_tamanho_vetor(vetor vetor_dinamico, int novo_tamanho);

/*
 * Adiciona um elemento ao vetor dinamico de forma ordenada
 */
void adicionar_elemento(vetor vetor_dinamico, TIPO_DOS_VALORES valor);

/*
 * Remove um elemento do vetor dinamico e mantem ordenado
 */
void remover_elemento(vetor vetor_dinamico, TIPO_DOS_VALORES valor);

/*
 * Desaloca da memoria o vetor dinamico
 */
void free_vetor(vetor vetor_dinamico);
