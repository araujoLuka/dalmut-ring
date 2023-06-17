#include "../essential.h"


//============================================



mensagem recebida;
mensagem enviada;

extern estado_jogo jogo;

extern maquina computador;

extern deck cartas;



//============================================




// envia uma mensagem
void enviar_mensagem(char tipo, char origem, char confirmacao, char conteudo1, char conteudo2) {

    usleep(10);

    //

    enviada.confirmacao = confirmacao;
    enviada.conteudo1 = conteudo1;
    enviada.conteudo2 = conteudo2;
    enviada.origem = origem;
    enviada.tipo = tipo;

    //

    struct sockaddr_in dest;
    size_t size;
    int nbytes;

    //
    
    dest.sin_family = AF_INET;
    dest.sin_addr.s_addr = inet_addr(computador.todos_ips[computador.id_next]);
    dest.sin_port = PORT;
    
    //

    size = sizeof (dest);
    nbytes = sendto(computador.socket, (char*) &enviada, sizeof(mensagem), 0, 
                 (struct sockaddr *) &dest, size);

    //

    if (nbytes < 0)
    {
        fprintf(stderr, "failure to send message\n");
        exit (EXIT_FAILURE);
    }

}


// espera para receber uma mensagem
// retorna 1 se uma mensagem foi recebida
// 0 se nao
int receber_mensagem() {

    char message[sizeof(mensagem)];

    struct sockaddr_in from;
    size_t size;
    int nbytes;

    //

    size = sizeof (from);

    nbytes = recvfrom(computador.socket, message, sizeof(mensagem), 0,
                   (struct sockaddr *) &from, (unsigned int *)&size);

    //

    if (nbytes < 0)
    {
        perror ("failure to receive message");
        exit (EXIT_FAILURE);
    }

    //

    strcpy((char*) &recebida, message);

    //

    return 1;

}



//-----------------------------------------------------------------



// verifica se a mensagem deu uma volta completa
// e se todos confirmaram ela
// 2 se deu volta completa e todos confirmaram
// 1 se deu volta completa e um erro ocorreu
// 0 se ainda nao deu volta completa
int verifica_confirmacoes() {
    fprintf(stderr, "DEBUGG: confirmacao recebida %d , confirmacao total %d\n", (int)recebida.confirmacao, (int)computador.confirmacao_completa);

    // caso a mensagem tenha dado uma volta completa
    if (recebida.origem == computador.id) {
        // caso todos confirmaram
        if ((computador.confirmacao_completa - recebida.confirmacao) == 0) {
            return 2;
        } else {
            // algo de errado aconteceu, um computador nao confirmou
            fprintf(stderr, "ERRO: um computador nao confirmou a mensagem\n");
            fprintf(stderr, "Encerrando o programa\n");

            jogo.estado_jogo = JOGO_ESTADO_EXIT;
            enviar_mensagem((char) MEN_EXIT, (char)computador.id, computador.confirm_biometria, 0, 0);

            return 1;
        }
    }

    return 0;
}



//-----------------------------------------------------------------



// recebe 1 mensagem e trata ela
void protocolo_de_tratamento() {

    fprintf(stderr, "DEBUGG: Entrou no protocolo de tratamento\n");

    // tranca o processo ate receber uma mensagem
    while(!receber_mensagem());

    //

    int status;

    //
    switch(recebida.tipo) {

        case (MEN_CONEXAO) :
            // confirma recebimento e manda adiante

            // caso tenha dado uma volta completa e todos confirmaram

            // manda novamente com conteudo alterado informando que o jogo comecou

            if (recebida.conteudo1 == 1) {
                jogo.estado_jogo = JOGO_ESTADO_COMPRANDO;
            }

            status = verifica_confirmacoes();
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
                    if (recebida.conteudo1 == 0) {
                        enviar_mensagem((char) MEN_CONEXAO, recebida.origem, recebida.confirmacao + computador.confirm_biometria, (char) 1, recebida.conteudo2);
                        protocolo_de_tratamento();
                    }
                    return;
                break;
            }

            enviar_mensagem((char) MEN_CONEXAO, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);

        break;

        case (MEN_BASTAO) :
            // checa se o campo de conteudo equivale ao id dessa maquina
            // se sim ela recebe o bastao e a mensagem acaba aqui,
            // se nao envia a mensagem para frente.

            // caso o id de origem seja o mesmo que o da maquina
            // significa q a mensagem deu uma volta mas nao achou o bastonete
            // manda MEN_EXIT

            // essa eh a maquina destino, coleta o bastao
            if (computador.id == recebida.conteudo1) {
                jogo.bastao = 1;
            }

            status = verifica_confirmacoes();
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

            enviar_mensagem((char) MEN_BASTAO, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);

        break;
        

        case (MEN_JOGO_INI) :
            // seta que o jogo iniciou apos todos ganharem suas cartas
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.estado_jogo = JOGO_ESTADO_INICIADO;

            status = verifica_confirmacoes();
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

            enviar_mensagem((char) MEN_JOGO_INI, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);

        break;


        case (MEN_JOGADOR_VENCEU) :
            // um jogador venceu, salva o seu id na lista de vencedores

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.id_terminados[jogo.qtd_terminados] = recebida.origem;
            jogo.qtd_terminados ++;

            //

            printf("Jogador %d  venceu\n", recebida.origem);

            //

            status = verifica_confirmacoes();
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

            enviar_mensagem((char) MEN_JOGADOR_VENCEU, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);

        break;


        case (MEN_COMPRANDO_CARTA) :
            // um jogador jogou cartas, printa na tela e salva a jogada

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel
            
            int nivel = recebida.conteudo1;
            int id_destino = recebida.conteudo2;

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

            status = verifica_confirmacoes();
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

            enviar_mensagem((char) MEN_COMPRANDO_CARTA, recebida.origem, recebida.confirmacao + computador.confirm_biometria, (char)recebida.conteudo1, (char)recebida.conteudo2);
        break;


        case (MEN_JOGADA) :
            // um jogador jogou cartas, printa na tela e salva a jogada

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.contador_pulos = 0;

            //

            jogo.lastPLayed_player = recebida.origem;
            jogo.lastPlayed_nivel = recebida.conteudo1;
            jogo.lastPlayed_quantidade = recebida.conteudo2;

            //

            printf("\n\nJogador %d jogou %dx cartas de nivel %d\n\n", jogo.lastPLayed_player, jogo.lastPlayed_nivel, jogo.lastPlayed_quantidade);

            //

            status = verifica_confirmacoes();
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

            enviar_mensagem((char) MEN_JOGADA, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);
        break;


        case (MEN_PULANDO) :
            // um jogador pulou sua vez

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel

            // analisa se a quantidade de pulos seguidos excedeu o limite
            // se sim lima as informacoes da rodada
            // e retorna o bastao para o ultimo id que jogou

            jogo.contador_pulos ++;

            status = verifica_confirmacoes();
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
            
            enviar_mensagem((char) MEN_PULANDO, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);

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

            status = verifica_confirmacoes();
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
            
            enviar_mensagem((char) MEN_RODADA_ACABOU, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);

        break;


        case (MEN_FIM) :
            // seta que o jogo acabou com todos tendo exaustado suas cartas
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da proxima maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.estado_jogo = JOGO_ESTADO_FIM;

            status = verifica_confirmacoes();
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
            
            enviar_mensagem((char) MEN_FIM, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);

        break;

        case (MEN_EXIT) :
            // seta para o jogo acabar prematuramente
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da proxima maquina
            // nao envia para frente a mensagem pq acabo o anel

            jogo.estado_jogo = JOGO_ESTADO_EXIT;

            status = verifica_confirmacoes();
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
            
            enviar_mensagem((char) MEN_EXIT, recebida.origem, recebida.confirmacao + computador.confirm_biometria, recebida.conteudo1, recebida.conteudo2);

        break;

    }

}
