#include "fila.h"
#include "operario.h"
#include "pilha.h"
#include "registro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int esteira_tamanho = 0, pilha_tamanho = 0, quantidade_de_pecas = 0;
  scanf("%d %d %d ", &esteira_tamanho, &pilha_tamanho, &quantidade_de_pecas);

  operario classificador = novo_operario(), embalador = novo_operario();
  fila esteira_classificacao = nova_fila(esteira_tamanho);
  pilha pilha_embalacao = nova_pilha(pilha_tamanho);
  registro registro_simulacao = novo_registro();

  printf("##### Simulação\n");
  for (int minuto_atual = 1;
       registro_simulacao->total_saida < quantidade_de_pecas; minuto_atual++) {
    /*
     * Embalacao
     */

    if (trabalhar_na_peca(embalador) && esta_segurando_peca(embalador)) {
      registro_simulacao->embalacao->saida++;
      registro_simulacao->total_saida++;
      free_peca(largar_peca(embalador));
    }

    if (esta_ociosso(embalador) && pilha_embalacao->tamanho_usado) {
      segurar_peca(embalador, desempilhar(pilha_embalacao));
      trabalhar_na_peca(embalador);
    }

    /*
     * Classificacao
     */
    if (trabalhar_na_peca(classificador) &&
        esta_segurando_peca(classificador) &&
        tamanho_disponivel_pilha(pilha_embalacao)) {
      registro_simulacao->classificacao->saida++;
      registro_simulacao->embalacao->entrada++;
      empilhar(pilha_embalacao, largar_peca(classificador));
    }
    if (esta_ociosso(classificador) && esteira_classificacao->tamanho_usado) {
      segurar_peca(classificador, desemfileira(esteira_classificacao));
      trabalhar_na_peca(classificador);
    }

    /*
     * Entrada
     */
    if (registro_simulacao->total_entrada < quantidade_de_pecas) {
      if (tamanho_disponivel_fila(esteira_classificacao)) {
        enfileira(esteira_classificacao, ler_peca_do_stdin());
        registro_simulacao->classificacao->entrada++;
        registro_simulacao->total_entrada++;
      } else {
        registro_simulacao->atrazo++;
      }
    }
    imprimir_relatorio_minuto(registro_simulacao, minuto_atual);
  }
  imprimir_relatorio_atrazo(registro_simulacao);

  free_registro(registro_simulacao);
  free_pilha(pilha_embalacao);
  free_fila(esteira_classificacao);
  free_operario(classificador);
  free_operario(embalador);
  return 0;
}
