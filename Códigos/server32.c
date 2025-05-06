#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 54321 // Porta correta conforme especificacao
#define MAX_PENDING 1     // Numero maximo de conexoes pendentes
#define MAX_LINE 256      // Tamanho maximo do buffer

int main() {
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    int len;
    int server_fd, new_socket;

    // Configurar o endereco do servidor
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    // Criar o socket
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    // Associar o socket ao endereco
    if (bind(server_fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("Erro no bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Escutar conexoes
    if (listen(server_fd, MAX_PENDING) < 0) {
        perror("Erro no listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor aguardando conexoes na porta %d...\n", SERVER_PORT);

    // Loop principal para aceitar conexoes
    while (1) {
        socklen_t addr_len = sizeof(sin);
        if ((new_socket = accept(server_fd, (struct sockaddr *)&sin, &addr_len)) < 0) {
            perror("Erro no accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        printf("Cliente conectado\n");

        // Loop para receber mensagens do cliente
        while ((len = recv(new_socket, buf, sizeof(buf), 0)) > 0) {
            buf[len] = '\0'; // Garantir que a string seja terminada
            printf("Mensagem recebida: %s\n", buf);
        }

        printf("Conexao com o cliente encerrada\n");
        close(new_socket); // Fechar conexao com o cliente
    }

    // Fechar o socket do servidor
    close(server_fd);
    return 0;
}
