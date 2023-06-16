#include <stdio.h>
#include <stdlib.h>

#include "../essential.h"




//============================================



maquina computador;

extern estado_jogo jogo;



//============================================




// le o arquivo setup.txt e salva seus dados
void ler_setup() {

    // abre o arquivo setup.txt
    FILE* file = fopen("../setup.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "ERRO: ao abrir arquivo setup.txt");
        return;
    }

    //

    // obtem quantas maquinas teremos no total
    fscanf(file, "%d", computador.qtd_maquinas);

    //

    // alloca o espaco para todos os ips
    computador.todos_ips = malloc(computador.qtd_maquinas * sizeof(char*));   // qtd de ips
    for (int i = 0; i < computador.qtd_maquinas; i++) {
        // 14 eh o numero de chars que um ip precisa +1 para determinar o fim da string
        computador.todos_ips[i] = malloc(14 * sizeof(char));
    }

    //

    // obtem os ips salvos em setup.txt
    for (int i = 0; i < computador.qtd_maquinas; i++) {
        fgets(computador.todos_ips[i], 14, file);
    }

}



//-----------------------------------------------------------------



// obtem o ip dessa maquina
void obtem_ip() {
    //computador->ip = obtem ip da propria maquina;
}


// tendo o ip, obtem a posicao de id dessa maquina na lista setup.txt
void obtem_id() {
    for (int i = 0; i < computador.qtd_maquinas; i++) {
        if (computador.ip == computador.todos_ips[i]) {
            computador.id = i;

            // sendo o primeiro id ele recebe o bastão
            if (computador.id == 0) {
                jogo.bastao = 1;
            }

            return;
        }
    }

    //

    fprintf(stderr, "ERRO: ip dessa maquina nao esta em setup.txt");
    return;
}



//-----------------------------------------------------------------



// inicia a coneccao entre os vizinhos
// tanto com o anterior quanto o proximo
void coneccao_com_vizinhos() {

    computador.id_next = (computador.id + 1) % computador.qtd_maquinas;

    if (computador.id_next == computador.id) {
        fprintf(stderr, "ERRO: id do proximo eh igual o atual");
        return;
    }

    //

    //computador->socket_next = obtem o socket da conecao

    //

    computador.id_prev = (computador.id - 1);
    if (computador.id_prev < 0) {
        computador.id_prev += computador.qtd_maquinas;
    }

    if (computador.id_prev == computador.id) {
        fprintf(stderr, "ERRO: id do anterior eh igual o atual");
        return;
    }

    //

    //computador->socket_next = obtem o socket da conecao

}
