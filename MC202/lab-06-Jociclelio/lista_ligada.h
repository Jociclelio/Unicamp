typedef struct no_lista_ligada *no;
typedef struct lista_ligada *lista;

struct no_lista_ligada {
  char *livro;
  no proximo;
};

struct lista_ligada {
  no inicio;
  no inserir;
  no fim;
};

/*
 * Aloca uma nova lista
 * e retorna o um ponteiro para ela
 */
lista nova_lista();

/*
 * Desaloca uma lista
 */
void free_lista(lista esse);

/*
 * Adiciona um livro na lista
 */
void adicionar_elemento(lista esse, char *livro, int livro_tamanho);

/*
 * Remove um livro da lista
 */
void remover_elemento(lista esse, char *livro);

/*
 * Define o local para iserir no inicio da lista
 */
void mover_inserir_inicio(lista esse);

/*
 * Define o local para iserir no final da lista
 */
void mover_inserir_fim(lista esse);

/*
 * imprimi a lista
 */
void imprimir(lista esse);
