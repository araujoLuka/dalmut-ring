typedef struct maquina {
    int qtd_maquinas;   // de setup.txt, obtem a quantidade de maquinas
    char** todos_ips;   // de setup.txt, obtem todos os ips em ordem

    char* ip;           // ip dessa maquina
    int id;             // id dessa maquina no arquivo setup.txt

    int socket_next;    // o socket aberto para a maquina posterios
    int socket_prev;    // o socket aberto para a maquina anterior

    int id_next;      // o id da maquina posterior
    int id_prev;      // o id da maquina anterior
    // os ips podem ser extrapolados da lista de ips
} maquina;
