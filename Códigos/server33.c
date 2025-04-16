#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 54321 // Porta correta conforme especificação
#define MAX_PENDING 5     // Número máximo de conexões pendentes
#define MAX_LINE 256      // Tamanho máximo do buffer

int main() {
    int server_fd, new_socket;
    struct sockaddr_in sin;
    char buf[MAX_LINE];
    int len;

    // Configurar o endereço do servidor
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    // Criar o socket
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    // Associar o socket ao endereço
    if (bind(server_fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("Erro no bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Escutar conexões
    if (listen(server_fd, MAX_PENDING) < 0) {
        perror("Erro no listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor aguardando conexões na porta %d...\n", SERVER_PORT);

    // Loop principal para aceitar conexões
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&sin, (socklen_t *)&len)) < 0) {
            perror("Erro no accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        printf("Cliente conectado\n");

        // Loop para alternar entre recv() e send()
        while ((len = recv(new_socket, buf, sizeof(buf), 0)) > 0) {
            buf[len] = '\0'; // Garantir que a string seja terminada
            printf("Mensagem recebida: %s\n", buf);

            // Enviar a mesma mensagem de volta ao cliente
            if (send(new_socket, buf, len, 0) < 0) {
                perror("Erro ao enviar mensagem");
                break;
            }
            printf("Mensagem enviada de volta: %s\n", buf);
        }

        printf("Conexão com o cliente encerrada\n");
        close(new_socket); // Fechar conexão com o cliente
    }

    // Fechar o socket do servidor
    close(server_fd);
    return 0;
}