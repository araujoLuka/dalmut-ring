#include <time.h>

#include "../essential.h"




//============================================



deck cartas;

extern estado_jogo jogo;


//============================================




// prepara o deck de cartas
// com 80 cartas distribuidas entre os niveis
void prepara_deck() {
    // preenche o deck com as cartas normais
    for (int i = 0; i < 12; i++) {
        cartas.cartas[i] = i;
    }

    // coloca 2 coringas
    cartas.cartas[13] = 2;
}



//-----------------------------------------------------------------



// aleatoriamente da as cartas para as outras maquinas
void dar_cartas() {
    // somente a primeira maquina pode ser o carteador
    if (jogo.bastao == 0) {
        return;
    }

    //

    prepara_deck();
    srand(time(NULL));

    //

    // elaborar como distribuir as cartas 1 por 1 do id 1 adiante, ate nao sobrar mais no deck

    //
}



//-----------------------------------------------------------------




// verifica se o jogador ainda possui cartas em maos
// retorna 1 se sim, e 0 se nao
int verificar_cartas() {
    for (int i = 0; i < 13; i++) {
        if (cartas.cartas[i] > 0) {
            return 0;
        }
    }

    return 1;
}
