#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 54321 // Porta correta conforme especificação
#define MAX_PENDING 1 // Número máximo de conexões pendentes
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from server";

    // Criar socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Erro na criação do socket");
        exit(EXIT_FAILURE);
    }

    // Configurar endereço do servidor
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Associar socket ao endereço
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
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

    printf("Servidor aguardando conexões na porta %d...\n", PORT);

    // Aceitar conexões
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) >= 0) {
        printf("Cliente conectado\n");

        // Ler mensagem do cliente
        read(new_socket, buffer, BUFFER_SIZE);
        printf("Mensagem recebida: %s\n", buffer);

        // Enviar resposta ao cliente
        send(new_socket, message, strlen(message), 0);
        printf("Mensagem enviada: %s\n", message);

        // Fechar conexão com o cliente
        close(new_socket);
    }

    if (new_socket < 0) {
        perror("Erro no accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return 0;
}