#include "./vetor_dinamico.h"
typedef int batedereco;
struct batmemoria_virtual {
  vetor memoria;
  vetor indices;
  int tamanho_minimo;
  int tamanho_usado;
};
typedef struct batmemoria_virtual *batmemoria;

/*
 * Cria uma nova batmemoria virtual
 */
batmemoria nova_memoria(int tamanho_inicial);

/*
 * Desaloca um vetor na batmemoria
 */
void free_batmemoria(batmemoria memoria);

/*
 * Aloca espaco para um vetor na batmemoria
 */
batedereco bat_alocar(batmemoria memoria, int tamanho, int indice_inicial);

/*
 * Dar free em um vetor na batmemoria
 */
void bat_free(batmemoria memoria, batedereco endereco);

/*
 * Recebe valores de um vetor do stdin e guarda na batmemoria
 */
void bat_amarzenar_de_stdin(batmemoria memoria, int tamanho);

/*
 * Mostra os valores de um vetor na batmemoria
 */
void bat_print(batmemoria memoria, batedereco endereco);

/*
 * Mosta o uso da batmemoria no stdout
 */
void bat_uso(batmemoria memoria);
