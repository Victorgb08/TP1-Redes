#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    socklen_t addr_len = sizeof(serv_addr);

    // Criar socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Configurar endereço do servidor
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "192.168.15.64", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return -1;
    }

    printf("Conectado ao servidor UDP. Digite mensagens (CTRL+C para sair):\n");

    // Loop para enviar e receber mensagens
    while (1) {
        printf("Você: ");
        fgets(message, BUFFER_SIZE, stdin);

        // Enviar mensagem ao servidor
        sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&serv_addr, addr_len);

        // Receber resposta do servidor
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serv_addr, &addr_len);
        if (bytes_received < 0) {
            perror("recvfrom failed");
            break;
        }

        printf("Servidor: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}