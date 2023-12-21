#include "sobrevivente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sobrevivente novo_sobrevivente(char *nome, int tamanho_nome, char *sobrenome,
                               int tamanho_sobrenome,
                               int numero_de_dias_sobrevividos) {
  sobrevivente novo = malloc(sizeof(struct estrutura_sobrevivente));
  novo->nome = malloc(tamanho_nome * sizeof(char));
  novo->sobrenome = malloc(tamanho_sobrenome * sizeof(char));
  strcpy(novo->nome, nome);
  strcpy(novo->sobrenome, sobrenome);
  novo->numero_de_dias_sobrevividos = numero_de_dias_sobrevividos;
  novo->indice_prato = -1;
  return novo;
}

sobrevivente novo_sobrevivente_de_stdin() {
  char nome[MAX_TAMANHO_NOME], sobrenome[MAX_TAMANHO_SOBRENOME];
  int tamanho_nome = 0, tamanho_sobrenome = 0,
      quantidade_de_dias_sobrevividos = 0;
  scanf("%[^ ]%*c%n %[^ ]%*c%n %d ", nome, &tamanho_nome, sobrenome,
        &tamanho_sobrenome, &quantidade_de_dias_sobrevividos);
  return novo_sobrevivente(nome, tamanho_nome, sobrenome, tamanho_sobrenome,
                           quantidade_de_dias_sobrevividos);
}

void free_sobrevivente(sobrevivente esse) {
  free(esse->nome);
  free(esse->sobrenome);
  free(esse);
}
