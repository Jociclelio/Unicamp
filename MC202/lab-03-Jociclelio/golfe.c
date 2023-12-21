#include "./partida.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int numero_de_partidas;
  scanf("%d ", &numero_de_partidas);

  for (int i = 1; i <= numero_de_partidas; i++) {
    partida *partida_atual = nova_partida_de_stdin(i);

    printf("Partida %d\n", partida_atual->id_partida);
    imprimir_numero_circuitos_e_jogadores(partida_atual);
    imprimir_preco_da_partida(partida_atual);
    imprimir_tabela_resultado(partida_atual);
    imprimir_circuito_mais_dificil(partida_atual);
    printf("##########\n");

    free_partida(partida_atual);
  }

  return 0;
}
