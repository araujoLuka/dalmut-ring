#include "../essential.h"




//============================================



maquina computador;

extern estado_jogo jogo;



//============================================




// le o arquivo setup.txt e salva seus dados
void ler_setup() {

    // abre o arquivo setup.txt
    FILE* file = fopen("./setup.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "ERRO: ao abrir arquivo setup.txt\n");
        return;
    }

    //

    // obtem quantas maquinas teremos no total
    fscanf(file, "%d", &computador.qtd_maquinas);

    //

    // alloca o espaco para todos os ips
    computador.todos_ips = malloc(computador.qtd_maquinas * sizeof(char*));   // qtd de ips
    for (int i = 0; i < computador.qtd_maquinas; i++) {
        // 14 eh o numero de chars que um ip precisa +1 para determinar o fim da string
        computador.todos_ips[i] = malloc(14 * sizeof(char));
    }

    //

    char buffer[14];

    // obtem os ips salvos em setup.txt
    for (int i = 0; i < computador.qtd_maquinas; i++) {
        fgets(buffer, 14, file);
        while(!strcmp(buffer, "\n")) {
            fgets(buffer, 14, file);
        }
        buffer[strcspn(buffer, "\n")] = 0;
        printf("%s\n", buffer);
        strcpy(computador.todos_ips[i], buffer);
    }

    //

    computador.confirmacao_completa = 0;
    int soma = 1;

    // calcula os bits de confirmacao quando completo
    for (int i = 0; i < computador.qtd_maquinas; i++) {
        soma += i;
        computador.confirmacao_completa += soma;
    }
    // caso tenha 4 maquinas
    // teremos cc = 64
    // ao fazer um xor desse valor com a confirmacao
    // se resultar em 0 ent todos os bits batem.

}



//-----------------------------------------------------------------



// abrir o socket
void abrir_socket() {
    computador.socket = socket(PF_INET, SOCK_DGRAM, 0);
    if (computador.socket < 0) {
        fprintf(stderr, "ERRO: na criacao socket\n");
    }

    //

    struct sockaddr_in name;
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = INADDR_ANY;
    name.sin_port = PORT;

    size_t size = sizeof(name);

    //

    if (bind (computador.socket, (struct sockaddr *) &name, size) < 0) {
        perror ("bind");
        exit (EXIT_FAILURE);
    }
}


// obtem o ip dessa maquina
void obtem_ip() {
    printf("Digite o seu IP: ");

    scanf("%s", computador.ip);
}


// tendo o ip, obtem a posicao de id dessa maquina na lista setup.txt
void obtem_id() {
    for (int i = 0; i < computador.qtd_maquinas; i++) {
        if (!strcmp(computador.ip, computador.todos_ips[i])) {
            computador.id = i;
            return;
        }
    }

    //

    fprintf(stderr, "ERRO: ip dessa maquina nao esta em setup.txt\n");
    return;
}



//-----------------------------------------------------------------



// inicia a coneccao entre os vizinhos
// tanto com o anterior quanto o proximo
void id_vizinhos() {

    computador.id_next = (computador.id + 1) % computador.qtd_maquinas;

    if (computador.id_next == computador.id) {
        fprintf(stderr, "ERRO: id do proximo eh igual o atual\n");
        return;
    }

    //

    computador.id_prev = (computador.id - 1);
    if (computador.id_prev < 0) {
        computador.id_prev += computador.qtd_maquinas;
    }

    if (computador.id_prev == computador.id) {
        fprintf(stderr, "ERRO: id do anterior eh igual o atual\n");
        return;
    }

}


// fecha o socket aberto
void encerra_coneccoes() {
    close(computador.socket);
}
