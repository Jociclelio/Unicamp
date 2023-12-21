#ifndef REGISTRO_H
#define REGISTRO_H
typedef struct estrutura_registro_etapa *registro_etapa;
typedef struct estrutura_registro *registro;

struct estrutura_registro_etapa {
  int entrada;
  int saida;
};

struct estrutura_registro {
  registro_etapa classificacao;
  registro_etapa embalacao;
  int total_entrada, total_saida;
  int atrazo;
};

/*
 * Aloca um novo registro
 */
registro novo_registro();

/*
 * Desaloca o registro da memoria
 */
void free_registro(registro esse);

/*
 * Imprimi o relatorio do minuto e reseta os registro_etapa
 */
void imprimir_relatorio_minuto(registro esse, int minuto);

/*
 * Imprimi o atrazo total
 */
void imprimir_relatorio_atrazo(registro esse);

#endif
