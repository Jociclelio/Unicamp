#define MAX_CARACTERE_POR_LINHA 200
#define MAX_CARACTERE_POR_SIMBOLO 50

enum conteudo_linha { DECLARACAO, OPERACAO, OUTRO };
typedef enum conteudo_linha conteudo_linha;

struct estrutura_acumulador_linha {
  char linha[MAX_CARACTERE_POR_LINHA];
  int numero_da_linha;
  conteudo_linha conteudo;
};
typedef struct estrutura_acumulador_linha *acumulador_linha;

/*
 * Aloca um novo acumulador
 */
acumulador_linha novo_acumulador();

/*
 * Desaloca um acumulador
 */
void free_acumulador(acumulador_linha esse);

/*
 * Ler a proxima expressao, pulando linhas com conteudo
 * igual a OUTRO ( ou diferentes de DECLARACAO e OPERACAO)
 */
int ler_proxima_expressao(acumulador_linha esse);
