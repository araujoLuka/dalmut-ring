#include "../essential.h"




//============================================



estado_jogo jogo;

extern mensagem recebida;
extern mensagem enviada;

extern maquina computador;

extern deck cartas;



//============================================




// passa o bastao para a proxima maquina
void passar_bastao(int id) {

    // remove o bastao desse computador
    jogo.bastao = 0;

    //

    enviar_mensagem((char) MEN_BASTAO, (char) computador.id, (1 << computador.id), (char)id, 0);
    protocolo_de_tratamento();
}



//-----------------------------------------------------------------



// verifica se todas as maquinas pularam seguido
// se sim envia mensagem para comecar uma nova rodada
void verifica_pulos_seguidos() {
    // se todas as maquinas pularam seguido
    if (jogo.contador_pulos >= computador.qtd_maquinas) {
        int id_last_played = jogo.lastPLayed_player;

        //

        enviar_mensagem((char) MEN_RODADA_ACABOU, (char) computador.id, (1 << computador.id), 0, 0);
        protocolo_de_tratamento();

        //

        passar_bastao(id_last_played);
    }
}



//-----------------------------------------------------------------



// decreta vitoria desse jogador
// envia mensagem a todos e para de jogar
void decreta_vitoria() {
    jogo.terminou = 1;

    //

    enviar_mensagem((char) MEN_JOGADOR_VENCEU, (char) computador.id, 0, 0, 0);
    protocolo_de_tratamento();
}


// verifica se esse eh o ultimo jogador faltando
// se sim decreta vitoria
int verifica_ultimo_jogador() {
    if (jogo.qtd_terminados >= computador.qtd_maquinas - 1) {
        // logo esse eh o ultimo jogador
        decreta_vitoria();
    }
}


// verifica condicao de vitoria
// se sim decreta vitoria
void verifica_vitoria() {
    if (!verificar_cartas()) {
        // ainda ha cartas nesse jogador
        return;
    }

    //

    decreta_vitoria();

}



//-----------------------------------------------------------------



int loop_jogo() {

    while(jogo.estado_jogo == JOGO_ESTADO_CONECCOES) {
        protocolo_de_tratamento();
    }

    //-----------------------------------------------------------------

    if (computador.id == 0) {
        prepara_deck();
    } else {
        limpa_deck();
    }

    //

    while(jogo.estado_jogo == JOGO_ESTADO_COMPRANDO) {
        if (!jogo.bastao) {
            printf("\nVoce nao possui o bastao, esperando mensagem...\n");
            protocolo_de_tratamento();
        }

        //

        if (jogo.bastao) {
            dar_cartas();

            //

            enviar_mensagem((char) MEN_JOGO_INI, computador.id, (1 << computador.id), 0, 0);
            protocolo_de_tratamento();
        }
    }

    //-----------------------------------------------------------------

    int input;
    while(jogo.estado_jogo == JOGO_ESTADO_INICIADO) {
        if (!jogo.bastao) {
            printf("\nVoce nao possui o bastao, esperando mensagem...\n");
            protocolo_de_tratamento();
        }

        //

        if (jogo.bastao) {
            if (jogo.terminou) {
                passar_bastao(computador.id_next);
            }

            //

            printa_cartas();

            printf("\nQual a sua acao?\n");
            printf("(1) jogar cartas\n");
            printf("(2) pular sua vez\n");
            printf("(3) ENCERRAR JOGO\n");

            scanf("%d", &input);
            
            //

            switch(input) {
                case(1) :   // Joga cartas
                    jogar_cartas();
                break;

                case(2) :   // Pula sua vez
                    enviar_mensagem((char) MEN_PULANDO, (char)computador.id, (1 << computador.id), 0, 0);
                    protocolo_de_tratamento();
                    passar_bastao(computador.id_next);
                break;

                case(3) :   // ENCERRA JOGO
                    enviar_mensagem((char) MEN_EXIT, (char)computador.id, (1 << computador.id), 0, 0);
                    protocolo_de_tratamento();
                break;
            }
        }

    }

    //-----------------------------------------------------------------

    if (jogo.estado_jogo == JOGO_ESTADO_FIM) {
        printf("\t\t\nJOGO ACABOU, todos os jogadores ganharam\n\n");

        printf("\trank:\n");

        // printa a lista de jogadores vitoriosos em ordem de vitoria
        int id;
        for (int i = 0; i < computador.qtd_maquinas; i++) {
            id = jogo.id_terminados[i];
            printf("\t - - - id: %3d  |  ip: %s\n", id, computador.todos_ips[id]);
        }
    }

    //

    if (jogo.estado_jogo == JOGO_ESTADO_EXIT) {
        fprintf(stderr, "\t\t\nJOGO ENCERRADO, input de usuario em alguma maquina\n");
    }

    //-----------------------------------------------------------------

    encerra_coneccoes();
    return 0;
}



//-----------------------------------------------------------------


// inicia as variaveis do jogo e alloca espaco
void init_jogo() {
    ler_setup();

    //

    jogo.bastao = 0;
    jogo.contador_pulos = 0;
    jogo.estado_jogo = JOGO_ESTADO_CONECCOES;

    jogo.id_terminados = malloc(computador.qtd_maquinas * sizeof(int));
    jogo.qtd_terminados = 0;

    jogo.lastPlayed_nivel = 0;
    jogo.lastPlayed_quantidade = 0;
    jogo.lastPLayed_player = 0;

    jogo.terminou = 0;

    //

    obtem_ip();
    obtem_id();

    //

    if (computador.id == 0) {
        jogo.bastao = 1;
    }

    //

    id_vizinhos();

    //

    loop_jogo();
}
