typedef struct estrurura_no *no;
struct estrurura_no {
  int vertice;
  no proximo;
};

/*
 * Desaloca uma lista ligada
 */
void free_lista(no esse);

/*
 * Isere um no na lista e
 * retorna o ponteiro da lista completa
 */
no insere_na_lista(no lista, int vertice);

/*
 * Remove um item da lista ligada e
 * retorna o ponteiro da lista completa
 */
no remove_da_lista(no lista, int vertice);
