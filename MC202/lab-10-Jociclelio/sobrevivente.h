#define MAX_TAMANHO_NOME 16
#define MAX_TAMANHO_SOBRENOME 16

typedef struct estrutura_sobrevivente *sobrevivente;
struct estrutura_sobrevivente {
  char *nome;
  char *sobrenome;
  int numero_de_dias_sobrevividos;
  int indice_prato;
};

/*
 * Aloca um novo sobrevivente na memoria
 */
sobrevivente novo_sobrevivente(char *nome, int tamanho_nome, char *sobrenome,
                               int tamanho_sobrenome,
                               int numero_de_dias_sobrevividos);

/*
 * Ler do stdin e Aloca um novo sobrevivente na memoria
 */
sobrevivente novo_sobrevivente_de_stdin();

/*
 * Desaloca um sobrevivente da memoria
 */
void free_sobrevivente(sobrevivente esse);
