#include "./batmemoria_virtual.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAMANHO_MAXIMO_DE_COMANDO 28

int main() {
  int numero_de_entradas = 0;
  batmemoria memoria = nova_memoria(8);

  scanf("%d ", &numero_de_entradas);

  for (int i = 0; i < numero_de_entradas; i++) {
    char comando[TAMANHO_MAXIMO_DE_COMANDO];
    scanf("%s ", comando);

    if (strcmp(comando, "bat-alloc") == 0) {
      int tamanho = 0;
      scanf("%d ", &tamanho);
      bat_amarzenar_de_stdin(memoria, tamanho);

    } else if (strcmp(comando, "bat-free") == 0) {
      batedereco endereco;
      scanf("%d ", &endereco);
      bat_free(memoria, endereco);

    } else if (strcmp(comando, "bat-print") == 0) {
      batedereco endereco;
      scanf("%d ", &endereco);
      bat_print(memoria, endereco);

    } else if (strcmp(comando, "bat-uso") == 0) {
      bat_uso(memoria);
    }
  }

  free_batmemoria(memoria);
  return 0;
}
