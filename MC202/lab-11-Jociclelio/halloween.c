#include "hash.h"
#include <stdio.h>

#define TAMANHO_MAX_COMANDO 15
#define TAMANHO_MAX_NOME 11
#define TAMANHO_MAX_SOBRENOME 11
#define TAMANHO_MAX_NOTA 11
/*
 * Hashes pre-calculados
 */
#define ENTRAR 948       /* "ENTRAR" */
#define SAIR 198         /* "SAIR" */
#define COMPRAR 207      /* "COMPRAR" */
#define TRICKORTREAT 264 /* "TRICKORTREAT" */
#define FINALIZAR 743    /* "FINALIZAR" */
#define BOA 34           /* "Boa" */
#define MEDIA 1121       /* "Média" */
#define RUIM 1235        /* "Ruim" */

/*
 * Retona a quantidade de doces
 * que uma fantasia merece de acordo
 * com nota da fantasia
 */
int nota_parser(char *nota) {
  switch (hash(nota)) {
  case BOA:
    return 3;
  case MEDIA:
    return 2;
  case RUIM:
    return 1;
  }
  return -1;
}

int main() {
  hash_table familias = novo_hash_table();
  char comando[TAMANHO_MAX_COMANDO], nome_familia[TAMANHO_MAX_NOME];
  char nome_crianca[TAMANHO_MAX_NOME], sobrenome_crianca[TAMANHO_MAX_SOBRENOME];
  int quantidade_de_doces, quantidade_de_casas;

  while (scanf("%s ", comando) != EOF) {
    switch (hash(comando)) {
    case ENTRAR: {
      scanf("%s %d ", nome_familia, &quantidade_de_doces);
      inserir(familias, nome_familia, quantidade_de_doces);
      break;
    }
    case SAIR: {
      scanf("%s ", nome_familia);
      printf("A familia %s saiu com %d doce(s) "
             "sobrando.\n",
             nome_familia, buscar(familias, nome_familia));
      remover(familias, nome_familia);
      break;
    }
    case COMPRAR: {
      scanf("%s %d ", nome_familia, &quantidade_de_doces);
      int *quantidade_de_doces_da_familia = dado(familias, nome_familia);
      *quantidade_de_doces_da_familia += quantidade_de_doces;
      printf("A familia %s agora possui %d doces.\n", nome_familia,
             *quantidade_de_doces_da_familia);
      break;
    }
    case TRICKORTREAT: {
      int qnt_doces_crianca = 0;
      scanf("%s %s %d ", nome_crianca, sobrenome_crianca, &quantidade_de_casas);

      /*
       * Visitas
       */
      for (int i = 0; i < quantidade_de_casas; i++) {
        char nota_familia[TAMANHO_MAX_NOTA];
        scanf("%s %s ", nome_familia, nota_familia);

        int qnt_doces_nota = nota_parser(nota_familia);
        int *qnt_doces_familia = dado(familias, nome_familia);

        if (qnt_doces_nota >= *qnt_doces_familia) {
          qnt_doces_nota = *qnt_doces_familia;
          if (*qnt_doces_familia)
            printf("A familia %s ficou sem doces.\n", nome_familia);
        }

        qnt_doces_crianca += qnt_doces_nota;
        *qnt_doces_familia -= qnt_doces_nota;
      }

      if (qnt_doces_crianca)
        printf("%s %s recebeu %d doce(s) das familias.\n", nome_crianca,
               sobrenome_crianca, qnt_doces_crianca);
      else
        printf("%s %s recebeu 10 doces da prefeitura.\n", nome_crianca,
               sobrenome_crianca);

      break;
    }
    case FINALIZAR: {
      free_hash_table(familias);
      return 0;
    }
    }
  }

  free_hash_table(familias);
  return 0;
}
