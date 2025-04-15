#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 54321 // Porta correta conforme especificação
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE];

    // Criar socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro na criação do socket");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Converter endereço IP para binário
    if (inet_pton(AF_INET, "192.168.15.64", &serv_addr.sin_addr) <= 0) {
        perror("Endereço inválido ou não suportado");
        return -1;
    }

    // Conectar ao servidor
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Falha na conexão");
        return -1;
    }

    printf("Conectado ao servidor. Digite mensagens (CTRL+C para sair):\n");

    // Loop para alternar entre send() e recv()
    while (1) {
        printf("Você: ");
        fgets(message, BUFFER_SIZE, stdin);

        // Enviar mensagem ao servidor
        send(sock, message, strlen(message), 0);

        // Receber resposta do servidor
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_read <= 0) {
            printf("Conexão encerrada pelo servidor\n");
            break;
        }

        printf("Servidor: %s\n", buffer);
    }

    close(sock);
    return 0;
}