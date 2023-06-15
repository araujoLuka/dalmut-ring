typedef struct machine {
    int qtd_maquinas;   // de setup.txt, obtem a quantidade de maquinas

    char* ip;           // ip dessa maquina

    int socket_next;    // o socket aberto para a maquina posterios
    int socket_prev;    // o socket aberto para a maquina anterior

    char* ip_next;      // o ip da maquina posterior
    char* ip_prev;      // o ip da maquina anterior

    int bastao;         // define se possui o bastao atualmente

} machine;