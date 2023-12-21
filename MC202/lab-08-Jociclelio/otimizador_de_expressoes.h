#include "arvore_expressoes.h"

#define NUMERO_DE_OPERADORES 8
/*
 * Retorna 1 se um caractere eh um operador
 */
int eh_operador(char caractere);

/*
 * Retorna 1 se o caractere e um numero
 */
int eh_numero(char caractere);

/*
 * Retorna 1 se o caractere eh uma variavel
 */
int eh_variavel(char caractere);

/*
 * Retorna 1 se o caractere eh um numero ou uma variavel
 */
int eh_variavel_ou_numero(char caractere);

/*
 * Rerona 1 se o caractere eh True ou False
 */
int eh_true_ou_false(char caractere);

/*
 * otimiza uma expressao
 */
void otimizar(arvore_binaria arvore, char dado);

/*
 * Otimiza de acordo com uma condicional passada por parametro
 */
void otimizar_condicional(arvore_binaria arvore, int comparacao);

/*
 * Otimiza expressao numerica
 * do tipo <numero> <operador> <numero>
 */
void otimizar_expressao_numerica(arvore_binaria arvore);

/*
 * Otimiza expressao logica do tipo
 * <T ou F> <operador> <expressao>
 */
void otimizar_expressao_logica(arvore_binaria arvore);

/*
 * otimizar expressoes pre determinadas pelo conjunto
 */
void otimizar_expressao_pre_determinada(arvore_binaria arvore);

/*
 * Otimiza expressao com base a situacao
 */
void otimizar_expressao(arvore_binaria arvore);

/*
 * Otimiza uma arvore de expressoes
 */
void otimizar_arvore_expressoes(arvore_binaria arvore);
