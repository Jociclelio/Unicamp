typedef struct {
  int id_circuito;
  int numero_de_participantes;
  int somatorio_de_jogadas;
  int *jogadas;
} circuito;

/*
 * Le do stdin o id do circuito do stdin
 */
void ler_id_circuito(circuito *esse_circuito);

/*
 * Le as jogadas do stdin e calcula o somatorio de jogadas
 */
void ler_jogadas(circuito *esse_circuito);
