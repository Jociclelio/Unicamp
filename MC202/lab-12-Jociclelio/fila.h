typedef struct estutura_fila *fila;
struct estutura_fila {
  int *pecas;
  int inicio;
  int fim;
  int tamanho_total;
  int tamanho_usado;
};

/*
 * Aloca uma noma fila na memoria
 */
fila nova_fila(int tamanho);

/*
 * Desaloca uma fila da memoria
 */
void free_fila(fila esse);

/*
 * Adiciona um valor no final da fila
 */
void enfileira(fila essa, int essa_peca);

/*
 * remove um valor da fila e retorna esse valor
 */
int desemfileira(fila essa);
