/*
 * Imprimi uma submatriz quadrada de inteiros stdout
 */
void imprimir_submatriz_quadrada(int **matriz, int submatriz_tamanho, int linha,
                                 int coluna);
/*
 * Chama a funcao imprimir_submatriz_quadrada passando a matriz
 * como submatriz
 */
void imprimir_matriz_quadrada(int **matriz, int matriz_tamanho);
/*
 * Retorna a soma de uma coluna de uma matriz de interios
 * Parametros:
 * int **matriz -> Matriz para soma
 * int inicial -> Indice inicial para soma na coluna
 * int final -> Indice final para soma
 * int coluna -> Coluna j para soma
 */
int soma_coluna(int **matriz, int inicial, int final, int coluna);

/*
 * Retorna a soma de uma coluna de uma matriz de interios
 * Parametros:
 * int **matriz -> Matriz para soma
 * int inicial -> Indice inicial para soma na coluna
 * int final -> Indice final para soma
 * int coluna -> Coluna j para soma
 * int sub_linha -> inicio_sublinha
 * int sub_coluna -> inicio_subcoluna
 */
int soma_subcoluna(int **matriz, int inicial, int final, int coluna,
                   int sub_linha, int sub_coluna);
/*
 * Retorna a soma de uma linha de uma matriz de interios
 * Parametros:
 * int **matriz -> Matriz para soma
 * int inicial -> Indice inicial para soma na linha
 * int final -> Indice final para soma
 * int linha -> linha j para soma
 */
int soma_linha(int **matriz, int inicial, int final, int linha);
/*
 * Retorna a soma de uma linha de uma matriz de interios
 * Parametros:
 * int **matriz -> Matriz para soma
 * int inicial -> Indice inicial para soma na linha
 * int final -> Indice final para soma
 * int linha -> linha j para soma
 * int sub_linha -> inicio_sublinha
 * int sub_coluna -> inicio_subcoluna
 */
int soma_sublinha(int **matriz, int inicial, int final, int linha,
                  int sub_linha, int sub_coluna);
/*
 * Edita um valor na submatriz
 * onde a posicao i,j e o valor vem do stdin
 */
void editar_submatriz_de_stdin(int **matriz, int linha, int coluna);
