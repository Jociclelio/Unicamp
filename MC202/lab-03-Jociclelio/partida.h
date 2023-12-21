#include "./circuito.h"
typedef struct {
  float valor_do_alugel;
  int id_partida;
  int indendificador_numerico;
  int numero_de_participantes;
  int numero_de_circuitos;
  int numero_de_equipamentos;
  circuito *circuitos;
} partida;

/*
 * Le uma nova partida do stdin
 */
partida *nova_partida_de_stdin(int id_partida);

/*
 * Le o numero de circuitos do stdin
 */
void ler_numero_de_circuitos(partida *essa_partida);

/*
 * Le o numero de jogadores do stdin
 */
void ler_numero_de_jogadores(partida *essa_partida);

/*
 * Le o numero de equipamentos do stdin
 */
void ler_numero_de_equipamentos(partida *essa_partida);

/*
 * Le os circuitos de uma partida do stdin
 */
void ler_circuitos(partida *essa_partida);

/*
 * Imprimi o numero de Jogadores, circuitos, e Equipamentos no stdout
 */
void imprimir_numero_circuitos_e_jogadores(partida *essa_partida);

/*
 * Imprimi o preco do aluguel no stdout
 */
void imprimir_preco_da_partida(partida *essa_partida);

/*
 * Imprimi o id do circuito mais dificil da partida no stdout
 * Imprimi o id do circuito com maior soma de jogadas no stdout
 */
void imprimir_circuito_mais_dificil(partida *essa_partida);

/*
 * Imprimi a pontuacao de cada jogador na partida no stdout
 */
void imprimir_tabela_resultado(partida *essa_partida);

/*
 * Libera da memoria usada pela partida
 */
void free_partida(partida *essa_partida);
