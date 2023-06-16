typedef struct game_state {
    int bastao;                 // define se possui o bastao atualmente

    int estado_jogo;             // Indica o estado atual do jogo
    //                              0 - SETANDO CONECCOES
    //                              1 - COMPRANDO CARTAS DO CARTEADOR
    //                              2 - JOGO INICIADO

    int terminou;               // define se esse jogador ja acabou suas cartas

    int* id_terminados;         // lista de id daqueles que ja terminaram em ordem de termino

    int lastPlayed_nivel;       // salva o nivel das ultimas cartas jogadas
    int lastPlayed_quantidade;  // salva a quantidade dessas
    int lastPLayed_player;      // salva quem foi o ultimo jogador a jogar

    int contador_pulos;         // contador de quantos jogadores pularam sem interrupcao
} game_state;
