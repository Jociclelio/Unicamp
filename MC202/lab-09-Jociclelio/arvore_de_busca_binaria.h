typedef struct estrutura_arvore_binaria *arvore_binaria;

enum cor { VERMELHO, PRETO };

struct estrutura_arvore_binaria {
  char chave[64];
  char dado[64];
  enum cor cor;
  arvore_binaria direita;
  arvore_binaria esquerda;
};

/*
 * Cria uma nova arvore_binaria e coloca o valor na raiz
 */
arvore_binaria nova_arvore_binaria(char *chave, char *dado,
                                   arvore_binaria direita,
                                   arvore_binaria esquerda, enum cor cor);

/*
 * Desaloca a arvore_binaria da memoria
 */
void free_arvore_binaria(arvore_binaria raiz_arvore);

/*
 * Imprimi a arvore de simbolos
 */
void imprimir_arvore_de_simbolos(arvore_binaria esse);

/*
 * Inseri na arvore de simbolos um novo simbolo
 */
arvore_binaria inserir(arvore_binaria esse, char *chave, char *dado);

/*
 * Busca na arvore de simbolos e retorna o no
 */
arvore_binaria buscar(arvore_binaria esse, char *chave);

/*
 * Busca na arvore de simbolos e retorna o dado
 */
char *buscar_simbolo(arvore_binaria esse, char *chave);
