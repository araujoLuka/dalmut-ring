typedef struct maquina {
    int qtd_maquinas;           // de setup.txt, obtem a quantidade de maquinas
    char** todos_ips;           // de setup.txt, obtem todos os ips em ordem

    int confirmacao_completa;   // salva o valor de todos as maquinas confirmarem
    // simplifica um pouco o codigo e impede calcular td hr isso

    char ip[14];                // ip dessa maquina
    int id;                     // id dessa maquina no arquivo setup.txt

    int socket;                 // o socket aberto para tds as maquinas


    int id_next;                // o id da maquina posterior
    int id_prev;                // o id da maquina anterior
    // os ips podem ser extrapolados da lista de ips
} maquina;



// abrir o socket
void abrir_socket();

// le o arquivo setup.txt e salva seus dados
void ler_setup();

// obtem o ip dessa maquina
void obtem_ip();

// tendo o ip, obtem a posicao de id dessa maquina na lista setup.txt
void obtem_id();

// inicia a coneccao entre os vizinhos
// tanto com o anterior quanto o proximo
void id_vizinhos();

//
void encerra_coneccoes();
