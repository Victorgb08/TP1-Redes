#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 54321 // Porta correta conforme especificação
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE] = {0};

    // Verificar se a mensagem foi passada como argumento ou via entrada padrão
    if (argc > 1) {
        strncpy(message, argv[1], BUFFER_SIZE - 1);
    } else {
        printf("Digite a mensagem para enviar ao servidor: ");
        fgets(message, BUFFER_SIZE, stdin);
        message[strcspn(message, "\n")] = '\0'; // Remover o caractere de nova linha
    }

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

    // Enviar mensagem ao servidor
    send(sock, message, strlen(message), 0);
    printf("Mensagem enviada: %s\n", message);

    // Ler resposta do servidor
    read(sock, buffer, BUFFER_SIZE);
    printf("Mensagem recebida: %s\n", buffer);

    // Fechar o socket
    close(sock);
    return 0;
}