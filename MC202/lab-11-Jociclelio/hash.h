#define MAX 1783

typedef struct estrutura_item *item;
struct estrutura_item {
  char chave[16];
  int dado;
};

typedef struct estrutura_hash_table *hash_table;
struct estrutura_hash_table {
  item *vetor;
  item removido;
  item vazio;
};

/*
 * Aloca um novo hash_table na memoria
 */
hash_table novo_hash_table();

/*
 * Libera uma hash_table da memoria
 */
void free_hash_table(hash_table esse);

/*
 * Executa a funcao de hash em uma string
 */
int hash(char *chave);

/*
 * Inseri na hash_table uma nova entrada de chave e dado
 */
void inserir(hash_table esse, char *chave, int dado);

/*
 * Remove da hash_table uma entrada de chave e dado
 */
void remover(hash_table esse, char *chave);

/*
 * Retorna o endereco de memoria do dado associado a uma chave
 */
int *dado(hash_table esse, char *chave);

/*
 * Retorna o dado associado a uma chave
 */
int buscar(hash_table esse, char *chave);
