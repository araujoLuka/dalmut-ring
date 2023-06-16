typedef struct mensagem {

    int conteudo;       // 2 bytes, nao sei como isso deve ficar
    char tipo;          // 1 byte, nao sei como isso deve ficar

    char origem;        // 1 byte, ao sei como isso deve ficar
    int confirmacao;    // 2 bytes, nao sei como isso deve ficar

} mensagem;


#define MEN_EXIT                0
#define MEN_FIM                 1
#define MEN_JOGADOR_VENCEU      2
#define MEN_JOGADA              3
#define MEN_COMPRANDO_CARTA     4
#define MEN_RODADA_ACABOU       5
#define MEN_BASTAO              6
#define MEN_CONECCAO            7
#define MEN_JOGO_INI            8


// envia uma mensagem
void enviar_mensagem(char tipo, char origem, int confirmacao, int conteudo);

// espera para receber uma mensagem
mensagem* receber_mensagem();
