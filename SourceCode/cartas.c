#include <time.h>

#include "../essential.h"




//============================================



deck cartas;

extern maquina computador;

extern estado_jogo jogo;

extern mensagem recebida;


//============================================




// prepara o deck de cartas
// com 80 cartas distribuidas entre os niveis
void prepara_deck() {
    // preenche o deck com as cartas normais
    for (int i = 0; i < 12; i++) {
        cartas.cartas[i] = i;
    }

    // coloca 2 coringas
    cartas.cartas[12] = 2;
}


// limpa o deck para ser usado
void limpa_deck() {
    // esvazia o deck
    for (int i = 0; i < 13; i++) {
        cartas.cartas[i] = 0;
    }
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



//-----------------------------------------------------------------



// desenha no stdout as cartas do jogador em ordem crescente
// melhor --> pior
void printa_cartas() {
    printf("\nSuas cartas atuais:\n\n");

    //

    for(int i = 0; i < 12; i++) {
        if (cartas.cartas[i] > 0) {
            printf("[%d] quantidade: %d\n", i, cartas.cartas[i]);
        }
    }

    //

    if (cartas.cartas[12] > 0) {
        printf("[Coringa] quantidade: %d\n", cartas.cartas[12]);
    }
} 



//-----------------------------------------------------------------



// faz os varios testes para poder jogar as cartas
// envia a mensagem das cartas jogadas
// testa se ganhou
// passa o bastao pro proximo
void jogar_cartas() {
    int nivel = 0;
    int quantidade = 0;
    int coringas = 0;

    //

    printf("Escolha um nivel (valor errado cancela)\n");
    scanf("%d", &nivel);

    //

    if (nivel <= 0 || nivel > 13) {
        printf("Nivel escolhido invalido, precisa ser entre 1 e 13\n");
        return;
    }

    if (cartas.cartas[nivel] == 0) {
        printf("Voce nao possui cartas desse nivel\n");
        return;
    }
    
    if (nivel > jogo.lastPlayed_nivel) {
        printf("Nivel escolhido eh maior que o ultimo nivel jogado\n");
        return;
    }

    //
    
    printf("Quantas cartas?\n");
    scanf("%d", &quantidade);

    //

    if (quantidade != jogo.lastPlayed_quantidade && jogo.lastPlayed_quantidade > 0) {
        printf("Quantidade escolhida nao eh igual a quantidade jogada anteriormente\n");
        return;
    }

    if (quantidade > cartas.cartas[nivel]) {
        printf("Voce nao tem tantas cartas nesse nivel\n");
        return;
    }

    if (quantidade <= 0) {
        printf("Quantidade invalida, precisa ser maior que 0\n");
        return;
    }

    //

    if (cartas.cartas[12] > 0 && nivel != 12) {
        printf("Quantos coringas deseja usar? (0 para nao usar nenhum)\n");
        scanf("%d", &coringas);

        //

        if (coringas < 0) {
            printf("Quantidade invalida, nao coloque valores negativos\n");
            return;
        }

        if (coringas > cartas.cartas[12]) {
            printf("Voce nao tem tantos coringas\n");
            return;
        }
    }

    //

    printf("\nJogada bem sucedida\n");
    printf("Jogando %dx cartas de nivel %d\n", quantidade, nivel);
    if (coringas > 0) {
        printf("junto com %dx coringas\n", coringas);
    }

    //

    cartas.cartas[nivel] -= quantidade;
    cartas.cartas[12] -= coringas;

    //

    enviar_mensagem((char) MEN_JOGADA, computador.id, computador.confirm_biometria, (char)nivel, (char)(quantidade + coringas));
    protocolo_de_tratamento();

    //

    // apos todos estarem cientes da jogada feita
    // verifica se esse jogador venceu nessa jogada
    verifica_vitoria();
    passar_bastao(computador.id_next);
}



//-----------------------------------------------------------------



// aleatoriamente da as cartas para as outras maquinas
// 1 por 1 em ordem 'horaria'
void dar_cartas() {
    int cartas_a_dar = 80;
    int id_prox_a_ganhar_carta = 0;

    //

    srand(time(NULL));

    //

    int nivel;

    //

    while(cartas_a_dar > 0) {
        if (id_prox_a_ganhar_carta != computador.id) {

            // gera um nivel de carta valido
            nivel = rand() % 13;
    
            // caso nao tenha mais essa carta
            // pula pra uma pior e re-testa
            while (cartas.cartas[nivel] == 0) {
                nivel = (nivel + 1) % 13;
            }
    
            //
            
            cartas.cartas[nivel] --;
            enviar_mensagem((char) MEN_COMPRANDO_CARTA, computador.id, computador.confirm_biometria, (char)nivel, (char)id_prox_a_ganhar_carta);
            protocolo_de_tratamento();

        }

        //

        id_prox_a_ganhar_carta = (id_prox_a_ganhar_carta + 1) % computador.qtd_maquinas;
        cartas_a_dar --;
    }
}
