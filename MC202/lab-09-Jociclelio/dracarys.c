#include "acumulador.h"
#include "arvore_de_busca_binaria.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define TRUE 1

int main() {
  acumulador_linha acumulador = novo_acumulador();
  arvore_binaria arvore_de_simbolos = NULL;
  int numero_de_erros = 0;

  while (TRUE) {
    if (ler_proxima_expressao(acumulador))
      break;

    switch (acumulador->conteudo) {
    case DECLARACAO: {
      char tipo[MAX_CARACTERE_POR_SIMBOLO],
          nome_variavel[MAX_CARACTERE_POR_SIMBOLO];
      sscanf(acumulador->linha, " %s %[^;]s", tipo, nome_variavel);
      arvore_de_simbolos = inserir(arvore_de_simbolos, nome_variavel, tipo);

    } break;
    case OPERACAO: {
      char nomes[3][MAX_CARACTERE_POR_SIMBOLO], operador, *tipos[3];
      sscanf(acumulador->linha, "%s %*s %s %c %[^;]s", nomes[0], nomes[1],
             &operador, nomes[2]);
      int indice_do_primeiro_nao_definido = -1;
      for (int i = 0; i < 3; i++) {
        tipos[i] = buscar_simbolo(arvore_de_simbolos, nomes[i]);
        if (!tipos[i] && indice_do_primeiro_nao_definido == -1)
          indice_do_primeiro_nao_definido = i;
      }
      if (indice_do_primeiro_nao_definido != -1) {
        printf("Linha %d: o símbolo %s não foi definido.\n",
               acumulador->numero_da_linha,
               nomes[indice_do_primeiro_nao_definido]);
        numero_de_erros++;
      } else if (strcmp(tipos[1], tipos[2])) {
        printf("Linha %d: tipos incompatíveis: %s (%s) %c %s "
               "(%s).\n",
               acumulador->numero_da_linha, nomes[1], tipos[1], operador,
               nomes[2], tipos[2]);
        numero_de_erros++;
      } else if (strcmp(tipos[0], tipos[1])) {
        printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, "
               "obteve %s.\n",
               acumulador->numero_da_linha, nomes[0], tipos[0], tipos[1]);
        numero_de_erros++;
      }
    } break;
    case OUTRO:
      break;
    }
  }

  if (!numero_de_erros)
    printf("Não há erros de tipo.\n");

  imprimir_arvore_de_simbolos(arvore_de_simbolos);
  free_acumulador(acumulador);
  free_arvore_binaria(arvore_de_simbolos);
  return 0;
}
