#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 54321 // Porta correta conforme especificação
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Criar socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Erro na criação do socket");
        exit(EXIT_FAILURE);
    }

    // Configurar endereço do servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Associar socket ao endereço
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Erro no bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor UDP aguardando mensagens na porta %d...\n", PORT);

    // Loop para receber e responder mensagens
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);

        // Receber mensagem do cliente
        int bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (bytes_received < 0) {
            perror("Erro no recvfrom");
            continue;
        }

        printf("Mensagem recebida: %s\n", buffer);

        // Enviar a mensagem de volta ao cliente
        sendto(sockfd, buffer, bytes_received, 0, (struct sockaddr *)&client_addr, addr_len);
        printf("Mensagem enviada de volta: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}