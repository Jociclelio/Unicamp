#include "fila_de_pedidos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1

int main() {
  int quantidade_de_planelas = 0, quantidade_de_sobreviventes = 0,
      quantidade_de_pedidos = 1, rodada = 0;

  scanf("%d %d ", &quantidade_de_planelas, &quantidade_de_sobreviventes);

  sobrevivente *sobreviventes =
      malloc(quantidade_de_sobreviventes * sizeof(sobrevivente));

  for (int i = 0; i < quantidade_de_sobreviventes; i++)
    sobreviventes[i] = novo_sobrevivente_de_stdin();

  fila_de_pedidos fila_de_pratos =
      nova_fila_de_pedidos(sobreviventes, quantidade_de_sobreviventes);

  while (quantidade_de_pedidos || fila_de_pratos->numero_usado) {
    if (scanf("%d ", &quantidade_de_pedidos) && quantidade_de_pedidos) {
      for (int i = 0; i < quantidade_de_pedidos; i++) {
        char comando[7];
        int id = -1;
        scanf("%s %d ", comando, &id);
        if (!strcmp(comando, "novo")) {
          char prato[26];
          int prato_tamanho = 0;
          scanf("%[^\n]%*c%n ", prato, &prato_tamanho);
          inserir_novo_pedido(fila_de_pratos, id, prato, prato_tamanho);
        } else if (!strcmp(comando, "altera")) {
          int valor = 0;
          scanf("%d ", &valor);
          mudar_prioridade_de_pedido(fila_de_pratos, id, valor);
        }
      }
    }
    if (fila_de_pratos->numero_usado) {
      rodada++;
      printf("---- rodada %d ----\n", rodada);
      for (int i = 0;
           i < quantidade_de_planelas && fila_de_pratos->numero_usado; i++) {
        pedido pedido = extrair_o_maximo(fila_de_pratos);
        printf("%s %s %s %d\n", sobreviventes[pedido->id]->nome,
               sobreviventes[pedido->id]->sobrenome, pedido->prato,
               pedido->valor);
        free_pedido(pedido);
      }
    }
  }

  for (int i = 0; i < quantidade_de_sobreviventes; i++)
    free_sobrevivente(sobreviventes[i]);
  free(sobreviventes);
  free_fila_de_pedidos(fila_de_pratos);
  return 0;
}
