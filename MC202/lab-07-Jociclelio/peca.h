#ifndef PECA_H
#define PECA_H

typedef struct estutura_peca *peca;
struct estutura_peca {
  char tamanho[32];
  int tipo;
  int tempo_etapa;
};

/*
 * Cria uma nova peca inicializando os
 * tempo_embalacao e tempo_clasificacao
 */
peca nova_peca(char *tamanho, int tipo);

/*
 * Ler uma peca nova do stdin
 */
peca ler_peca_do_stdin();

/*
 * Inicializa o camp tempo_etapa para o
 * tempo para classificar
 */
void inicializar_tempo_classificacao(peca essa);

/*
 * Inicializao o campo tempo_etapa para
 * tempo para embalar
 */
void inicializar_tempo_embalacao(peca essa);

/*
 * Desaloca um peca da memoria
 */
void free_peca(peca essa);

#endif
