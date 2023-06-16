#include "../essential.h"


//============================================



mensagem recebida;
mensagem enviada;



//============================================




// envia uma mensagem
void enviar_mensagem(char tipo, char origem, int confirmacao, int conteudo) {

}


// espera para receber uma mensagem
mensagem* receber_mensagem() {

    // recebe a mensagem

    //

    switch(recebida.tipo) {

        case (MEN_BASTAO) :
            // checa se o campo de conteudo equivale ao id dessa maquina
            // se sim ela recebe o bastao e a mensagem acaba aqui,
            // se nao envia a mensagem para frente.

            // caso o id de origem seja o mesmo que o da maquina
            // significa q a mensagem deu uma volta mas nao achou o bastonete
            // manda MEN_EXIT
        break;

        case (MEN_FIM) :
            // seta que o jogo acabou com todos tendo exaustado suas cartas
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel
        break;

        case (MEN_EXIT) :
            // seta para o jogo acabar prematuramente
            // envia a mensagem para frente

            // caso o id de origem seja o mesmo que o da maquina
            // nao envia para frente a mensagem pq acabo o anel
        break;

    }

}
