#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#define TIPO_DOS_DADOS_ARVORE_BINARIA char

typedef struct estrutura_arvore_binaria *arvore_binaria;
struct estrutura_arvore_binaria {
  TIPO_DOS_DADOS_ARVORE_BINARIA dado;
  arvore_binaria direita;
  arvore_binaria esquerda;
};

/*
 * Cria uma nova arvore_binaria e coloca o valor na raiz
 */
arvore_binaria nova_arvore_binaria(TIPO_DOS_DADOS_ARVORE_BINARIA dado,
                                   arvore_binaria direita,
                                   arvore_binaria esquerda);

/*
 * Desaloca a arvore_binaria da memoria
 */
void free_arvore_binaria(arvore_binaria raiz_arvore);

#endif
