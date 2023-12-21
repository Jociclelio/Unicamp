#include "acumulador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Aloca um novo acumulador
 */
acumulador_linha novo_acumulador() {
  acumulador_linha novo = malloc(sizeof(struct estrutura_acumulador_linha));
  novo->numero_da_linha = 0;
  return novo;
}

/*
 * Desaloca um acumulador
 */
void free_acumulador(acumulador_linha esse) { free(esse); }

/*
 * Verifica se um charactere e parenteses
 */
int eh_parentesses(char charactere) {
  return charactere == '(' || charactere == ')';
}

/*
 * Verifica se um charactere e cochetes
 */
int eh_cochetes(char charactere) {
  return charactere == '{' || charactere == '}';
}

/*
 * Verifica se uma string tem parenteses ou cochetes
 */
int tem_parenteses_ou_cochetes(char *string) {
  for (int i = 0; string[i] != '\0'; i++)
    if (eh_parentesses(string[i]) || eh_cochetes(string[i]))
      return 1;
  return 0;
}

/*
 * Verifica se o charactere e uma letra
 */
int eh_letra(char charactere) {
  return ((charactere >= 'A') && (charactere <= 'Z')) ||
         ((charactere >= 'a') && (charactere <= 'z'));
}

/*
 * Verifica se a primeira sub_string de um string eh
 * a string "return"
 */
int eh_return(char *string) {
  char sub_string[MAX_CARACTERE_POR_SIMBOLO];
  sscanf(string, " %s", sub_string);
  if (!strcmp("return", sub_string))
    return 1;
  return 0;
}

/*
 * Verifica se o primeiro digito de uma string
 * e uma letra
 */
int comeca_com_letra(char *string) {
  char charactere = '\0';
  sscanf(string, " %c", &charactere);
  return eh_letra(charactere);
}

/*
 * Verifica se a primeira sub_string de uma string e
 * char ou int ou double
 */
int eh_declaracao(char *string) {
  char sub_string[MAX_CARACTERE_POR_SIMBOLO];
  sscanf(string, " %s", sub_string);
  if (!strcmp("char", sub_string) || !strcmp("double", sub_string) ||
      !strcmp("int", sub_string))
    return 1;
  return 0;
}

/*
 * Verifica se a string tem somente um charactere de espaco
 */
int eh_linha_vazia(char *string) {
  return string[0] == ' ' && string[1] == '\0';
}

/*
 * Classifica o conteudo da linha
 */
conteudo_linha conteudo_da_linha(char *linha) {
  if (tem_parenteses_ou_cochetes(linha) || !comeca_com_letra(linha) ||
      eh_linha_vazia(linha) || eh_return(linha))
    return OUTRO;
  else if (eh_declaracao(linha))
    return DECLARACAO;
  else
    return OPERACAO;
}

/*
 * ler uma linha do stdin
 */
void ler_linha(acumulador_linha esse) {
  fgets(esse->linha, MAX_CARACTERE_POR_LINHA, stdin);
  esse->conteudo = conteudo_da_linha(esse->linha);
  esse->numero_da_linha++;
}

/*
 * Ler a proxima expressao, pulando linhas com conteudo
 * igual a OUTRO ( ou diferentes de DECLARACAO e OPERACAO)
 */
int ler_proxima_expressao(acumulador_linha esse) {
  if (feof(stdin))
    return 1;

  ler_linha(esse);
  if (esse->conteudo == OUTRO)
    return ler_proxima_expressao(esse);

  return 0;
}
