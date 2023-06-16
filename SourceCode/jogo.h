typedef struct estado_jogo {
    int bastao;                 // define se possui o bastao atualmente

    int estado_jogo;             // Indica o estado atual do jogo
    //                              0 - SETANDO CONECCOES
    //                              1 - COMPRANDO CARTAS DO CARTEADOR
    //                              2 - JOGO INICIADO
    //                              3 - JOGO ACABOU POR VITORIA
    //                              4 - JOGO ACABOU POR SAIDA DE INPUT

    int terminou;               // define se esse jogador ja acabou suas cartas

    int* id_terminados;         // lista de id daqueles que ja terminaram em ordem de termino
    int qtd_terminados;         // quantos jogadores ja terminaram

    int lastPlayed_nivel;       // salva o nivel das ultimas cartas jogadas
    int lastPlayed_quantidade;  // salva a quantidade dessas
    int lastPLayed_player;      // salva quem foi o ultimo jogador a jogar

    int contador_pulos;         // contador de quantos jogadores pularam sem interrupcao
} estado_jogo;




#define JOGO_ESTADO_CONECCOES       0
#define JOGO_ESTADO_COMPRANDO       1   // DONE
#define JOGO_ESTADO_INICIADO        2   // DONE
#define JOGO_ESTADO_FIM             3   // DONE
#define JOGO_ESTADO_EXIT            4   // DONE




// passa o bastao para a proxima maquina
void passar_bastao(int id);


// verifica se todas as maquinas pularam seguido
// se sim envia mensagem para comecar uma nova rodada
void verifica_pulos_seguidos();

// verifica condicao de vitoria
// se sim decreta vitoria
void verifica_vitoria()

// inicia as variaveis do jogo e alloca espaco
void init_jogo();
