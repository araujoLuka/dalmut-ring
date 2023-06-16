#include "../essential.h"




//============================================



estado_jogo jogo;

extern mensagem recebida;
extern mensagem enviada;

extern maquina computador;



//============================================




// passa o bastao para a proxima maquina
void passar_bastao() {

    // des seta o bastao nessa
    jogo.bastao = 0;

    //

    char tipo = (char) 3;

    enviar_mensagem((char) MEN_BASTAO, (char) computador.id, 0, computador.id_next);

}



//-----------------------------------------------------------------



// verifica se esse eh o ultimo jogador faltando
int verifica_ultimo_jogador() {
    
}


// verifica condicao de vitoria
// se sim envia mensagem a todos e para de jogar
void verifica_vitoria() {
    if (!verificar_cartas()) {
        // ainda ha cartas nesse jogador
        return;
    }

    jogo.terminou = 1;

    //

    enviar_mensagem((char) MEN_JOGADOR_VENCEU, (char) computador.id, 0, 0);

    //

    passar_bastao();

}
