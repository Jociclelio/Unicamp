#include "./partida.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Le uma nova partida do stdin
 */
partida *nova_partida_de_stdin(int id_partida) {
  partida *nova_partida = malloc(sizeof(partida));
  nova_partida->id_partida = id_partida;
  ler_numero_de_jogadores(nova_partida);
  ler_numero_de_circuitos(nova_partida);
  ler_numero_de_equipamentos(nova_partida);
  ler_circuitos(nova_partida);
  return nova_partida;
}

/*
 * Le o numero de circuitos do stdin
 */
void ler_numero_de_circuitos(partida *essa_partida) {
  scanf("%d ", &essa_partida->numero_de_circuitos);
}

/*
 * Le o numero de jogadores do stdin
 */
void ler_numero_de_jogadores(partida *essa_partida) {
  scanf("%d ", &essa_partida->numero_de_participantes);
}

/*
 * Le o numero de equipamentos do stdin
 */
void ler_numero_de_equipamentos(partida *essa_partida) {
  scanf("%d ", &essa_partida->numero_de_equipamentos);
}

/*
 * Le os circuitos de uma partida do stdin
 */
void ler_circuitos(partida *essa_partida) {
  essa_partida->circuitos =
      malloc(essa_partida->numero_de_circuitos * sizeof(circuito));
  for (int i = 0; i < essa_partida->numero_de_circuitos; i++) {
    essa_partida->circuitos[i].numero_de_participantes =
        essa_partida->numero_de_participantes;
    ler_id_circuito(essa_partida->circuitos + i);
    ler_jogadas(essa_partida->circuitos + i);
  }
}

/*
 * Imprimi o numero de Jogadores, circuitos, e Equipamentos no stdout
 */
void imprimir_numero_circuitos_e_jogadores(partida *essa_partida) {
  printf("Num. de Jogadores: %d - Num. de Circuitos: %d - Num. de "
         "Equipamentos: %d\n",
         essa_partida->numero_de_participantes,
         essa_partida->numero_de_circuitos,
         essa_partida->numero_de_equipamentos);
}

/*
 * Imprimi o preco do aluguel no stdout
 */
void imprimir_preco_da_partida(partida *essa_partida) {
  essa_partida->valor_do_alugel = 10 * essa_partida->numero_de_circuitos +
                                  17.5 * essa_partida->numero_de_equipamentos;
  printf("Valor do Aluguel: R$ %.2f\n", essa_partida->valor_do_alugel);
}

/*
 * Imprimi o id do circuito mais dificil da partida no stdout
 * Imprimi o id do circuito com maior soma de jogadas no stdout
 */
void imprimir_circuito_mais_dificil(partida *essa_partida) {
  int id_circuito_mais_dificil, soma_maior = 0;

  for (int i = 0; i < essa_partida->numero_de_circuitos; i++) {
    int soma_atual = essa_partida->circuitos[i].somatorio_de_jogadas;
    if (soma_atual > soma_maior) {
      id_circuito_mais_dificil = essa_partida->circuitos[i].id_circuito;
      soma_maior = soma_atual;
    }
  }
  printf("Circuito mais dificil: %d\n", id_circuito_mais_dificil);
}

/*
 * Imprimi a pontuacao de cada jogador na partida no stdout
 */
void imprimir_tabela_resultado(partida *essa_partida) {
  for (int i = 0; i < essa_partida->numero_de_participantes; i++) {
    int pontuacao = 0;
    for (int j = 0; j < essa_partida->numero_de_circuitos; j++)
      pontuacao += essa_partida->circuitos[j].jogadas[i];
    printf("Jogador %d: %d\n", i + 1, pontuacao);
  }
}

/*
 * Libera da memoria usada pela partida
 */
void free_partida(partida *essa_partida) {
  for (int j = 0; j < essa_partida->numero_de_circuitos; j++)
    free(essa_partida->circuitos[j].jogadas);
  free(essa_partida->circuitos);
  free(essa_partida);
}
