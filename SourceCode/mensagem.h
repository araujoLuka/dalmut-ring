typedef struct mensagem {

    int conteudo;       // 2 bytes, nao sei como isso deve ficar

    // para jogadas ou dando cartas
    // 1 byte sera para o tipo de carta
    // 2 byte para a quantidade         (255 max, mas so usaremos, 14(0000 1110) no maximo do maximo)

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
#define MEN_CONECCAO            8   //
#define MEN_JOGO_INI            9   // DONE


// envia uma mensagem
void enviar_mensagem(char tipo, char origem, int confirmacao, int conteudo);


// recebe 1 mensagem e trata ela
void protocolo_de_tratamento();
