#include "../essential.h"


//============================================



mensagem recebida;
mensagem enviada;

extern estado_jogo jogo;

extern maquina computador;

extern deck cartas;



//============================================




// envia uma mensagem
void enviar_mensagem(char tipo, char origem, int confirmacao, int conteudo) {
    
    // verifica coneccao com o proximo id
    
    //

    // envia mensagem para o proximo id

}


// espera para receber uma mensagem
// retorna 1 se uma mensagem foi recebida
// 0 se nao
int receber_mensagem() {

    // recebe a mensagem

    //

    // desmembra ela e salva nos campos da variavel 'mensagem recebida'

    //

    // return 1 ou 0

}



//-----------------------------------------------------------------



// verifica se a mensagem deu uma volta completa
// e se todos confirmaram ela
// 2 se deu volta completa e todos confirmaram
// 1 se deu volta completa e um erro ocorreu
// 0 se ainda nao deu volta completa
int verifica_confirmacoes() {

    // caso a mensagem tenha dado uma volta completa
    if (recebida.origem == computador.id) {

        // caso todos confirmaram
        if ((computador.confirmacao_completa ^ recebida.confirmacao) == 0) {
            return 2;
        } else {
            // algo de errado aconteceu, um computador nao confirmou
            fprintf(stderr, "ERRO: um computador nao confirmou a mensagem\n");
            fprintf(stderr, "Encerrando o programa\n");

            jogo.estado_jogo = JOGO_ESTADO_EXIT;
            enviar_mensagem((char) MEN_EXIT, (char)computador.id, (1 << computador.id), 0);

            return 1;
        }
    }

    return 0;
}



//-----------------------------------------------------------------



// recebe 1 mensagem e trata ela
void protocolo_de_tratamento() {

    // tranca o processo ate receber uma mensagem
    while(!receber_mensagem());

    //

    switch(recebida.tipo) {

        case (MEN_BASTAO) :
            // checa se o campo de conteudo equivale ao id dessa maquina
            // se sim ela recebe o bastao e a mensagem acaba aqui,
            // se nao envia a mensagem para frente.

            // caso o id de origem seja o mesmo que o da maquina
            // significa q a mensagem deu uma volta mas nao achou o bastonete
            // manda MEN_EXIT

            // essa eh a maquina destino, coleta o bastao
            if (computador.id == recebida.conteudo) {
                jogo.bastao = 1;
            }

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja
                    // assumimos que o bastao nao pode ser perdido
                    return;
                break;
            }

            enviar_mensagem((char) MEN_BASTAO, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);

        break;
        

        case (MEN_JOGO_INI) :
            // seta que o jogo iniciou apos todos ganharem suas cartas
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.estado_jogo = JOGO_ESTADO_INICIADO;

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja
                    return;
                break;
            }

            enviar_mensagem((char) MEN_JOGO_INI, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);

        break;


        case (MEN_JOGADOR_VENCEU) :
            // um jogador venceu, salva o seu id na lista de vencedores

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.id_terminados[jogo.qtd_terminados] = recebida.origem;
            jogo.qtd_terminados ++;

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja
                    return;
                break;
            }

            enviar_mensagem((char) MEN_JOGADOR_VENCEU, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);

        break;


        case (MEN_COMPRANDO_CARTA) :
            // um jogador jogou cartas, printa na tela e salva a jogada

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel
            
            int nivel = (255 & recebida.conteudo);
            // coleta os primeiros 8 bits da mensagem
            int id_destino = (recebida.conteudo >> 8);
            // coleta os proximos 8 bits da mensagem

            //

            if (id_destino == computador.id) {
                if (nivel < 12) {
                    printf("Recebido uma carta %d\n", nivel);
                } else {
                    printf("Recebido um coringa\n");
                }

                cartas.cartas[nivel] ++;
            }

            //

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja
                    return;
                break;
            }

            enviar_mensagem((char) MEN_COMPRANDO_CARTA, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);
        break;


        case (MEN_JOGADA) :
            // um jogador jogou cartas, printa na tela e salva a jogada

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.contador_pulos = 0;

            //

            jogo.lastPLayed_player = recebida.origem;
            jogo.lastPlayed_nivel = (255 & recebida.conteudo);
            // coleta os primeiros 8 bits da mensagem
            jogo.lastPlayed_quantidade = (recebida.conteudo >> 8);
            // coleta os proximos 8 bits da mensagem

            //

            printf("\n\nJogador %d jogou %dx cartas de nivel %d\n\n", jogo.lastPLayed_player, jogo.lastPlayed_nivel, jogo.lastPlayed_quantidade);

            //

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja
                    return;
                break;
            }

            enviar_mensagem((char) MEN_JOGADA, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);
        break;


        case (MEN_PULANDO) :
            // um jogador pulou sua vez

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel

            // analisa se a quantidade de pulos seguidos excedeu o limite
            // se sim lima as informacoes da rodada
            // e retorna o bastao para o ultimo id que jogou

            jogo.contador_pulos ++;

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja

                    verifica_pulos_seguidos();

                    return;
                break;
            }
            
            enviar_mensagem((char) MEN_PULANDO, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);

        break;


        case (MEN_RODADA_ACABOU) :
            // printa na tela que a rodada acabou e vai recomecar
            // reinicia os valores das ultimas jogadas
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da proxima maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.lastPlayed_nivel = 0;
            jogo.lastPlayed_quantidade = 0;
            jogo.lastPLayed_player = 0;

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja
                    return;
                break;
            }
            
            enviar_mensagem((char) MEN_RODADA_ACABOU, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);

        break;


        case (MEN_FIM) :
            // seta que o jogo acabou com todos tendo exaustado suas cartas
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da proxima maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.estado_jogo = JOGO_ESTADO_FIM;

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja
                    return;
                break;
            }
            
            enviar_mensagem((char) MEN_FIM, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);

        break;

        case (MEN_EXIT) :
            // seta para o jogo acabar prematuramente
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da proxima maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.estado_jogo = JOGO_ESTADO_EXIT;

            int status = verifica_confirmacoes();
            switch (status) {
                case (0) :
                    // ainda falta maquinas a receber
                break;

                case (1) :
                    // um erro aconteceu, sai do codigo
                    return;
                break;

                case (2) :
                    // todos receberam a mensagem ja
                    return;
                break;
            }
            
            enviar_mensagem((char) MEN_EXIT, recebida.origem, recebida.confirmacao | (1 << computador.id), recebida.conteudo);

        break;

    }

}
