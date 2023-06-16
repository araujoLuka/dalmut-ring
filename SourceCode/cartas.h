typedef struct deck {
    int cartas[13];      // 13 slots para cada tipo de carta que se pode ter
} deck;




// prepara o deck de cartas
// com 80 cartas distribuidas entre os niveis
void prepara_deck();

// limpa o deck para ser usado
void limpa_deck();

// verifica se o jogador ainda possui cartas em maos
// retorna 1 se sim, e 0 se nao
int verificar_cartas();


// desenha no stdout as cartas do jogador em ordem crescente
// melhor --> pior
void printa_cartas();


// faz os varios testes para poder jogar as cartas
// envia a mensagem das cartas jogadas
// testa se ganhou
// passa o bastao pro proximo
void jogar_cartas();


// aleatoriamente da as cartas para as outras maquinas
// 1 por 1 em ordem 'horaria'
void dar_cartas();
