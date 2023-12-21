#include "lista_ligada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_MAXIMO_DO_COMANDO 16
#define TAMANHO_MAXIMO_DO_LIVRO 64

int main() {
  char comando[TAMANHO_MAXIMO_DO_COMANDO];
  lista lista_de_livros = nova_lista();

  while (scanf("%s ", comando) != EOF) {
    char livro[TAMANHO_MAXIMO_DO_LIVRO];

    if (!strcmp(comando, "adicionar")) {
      int livro_tamanho = 0;
      scanf("%[^\n]%*c%n", livro, &livro_tamanho);
      adicionar_elemento(lista_de_livros, livro, livro_tamanho);

    } else if (!strcmp(comando, "inicio")) {
      mover_inserir_inicio(lista_de_livros);

    } else if (!strcmp(comando, "final")) {
      mover_inserir_fim(lista_de_livros);

    } else if (!strcmp(comando, "remover")) {
      scanf("%[^\n]c ", livro);
      remover_elemento(lista_de_livros, livro);

    } else if (!strcmp(comando, "imprimir")) {
      imprimir(lista_de_livros);
    }
  }

  free_lista(lista_de_livros);
  return 0;
}
