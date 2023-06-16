typedef struct mensagem {

    char conteudo1;       // 1 byte de conteudo
    char conteudo2;       // 1 byte de conteudo 2
    // (255 max, mas so usaremos, 14(0000 1110) no maximo do maximo)

    char tipo;          // 1 byte, nao sei como isso deve ficar

    char origem;        // 1 byte, ao sei como isso deve ficar
    int confirmacao;    // 2 bytes, nao sei como isso deve ficar

} mensagem;


#define MEN_EXIT                0   // DONE
#define MEN_FIM                 1   // DONE
#define MEN_JOGADOR_VENCEU      2   // DONE
#define MEN_JOGADA              3   // DONE
#define MEN_PULANDO             4   // DONE
#define MEN_COMPRANDO_CARTA     5   // DONE
#define MEN_RODADA_ACABOU       6   // DONE
#define MEN_BASTAO              7   // DONE
#define MEN_CONEXAO             8   // DONE
#define MEN_JOGO_INI            9   // DONE


// envia uma mensagem
void enviar_mensagem(char tipo, char origem, int confirmacao, char conteudo1, char conteudo2);


// recebe 1 mensagem e trata ela
void protocolo_de_tratamento();
