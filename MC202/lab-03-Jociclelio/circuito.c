#include "./circuito.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Le do stdin o id do circuito do stdin
 */
void ler_id_circuito(circuito *esse_circuito) {
  scanf("%d ", &esse_circuito->id_circuito);
}

/*
 * Le as jogadas do stdin e calcula o somatorio de jogadas
 */
void ler_jogadas(circuito *esse_circuito) {
  esse_circuito->jogadas =
      malloc(esse_circuito->numero_de_participantes * sizeof(int));
  esse_circuito->somatorio_de_jogadas = 0;
  for (int i = 0; i < esse_circuito->numero_de_participantes; i++) {
    scanf("%d ", &esse_circuito->jogadas[i]);
    esse_circuito->somatorio_de_jogadas += esse_circuito->jogadas[i];
  }
}
