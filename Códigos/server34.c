#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 54321 // Porta correta conforme especificação
#define MAX_LINE 256      // Tamanho máximo do buffer

int main() {
    int sockfd;
    struct sockaddr_in sin, client_addr;
    char buf[MAX_LINE];
    socklen_t client_len = sizeof(client_addr);

    // Criar socket UDP
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Erro ao criar o socket");
        exit(EXIT_FAILURE);
    }

    // Configurar o endereço do servidor
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(SERVER_PORT);

    // Associar o socket ao endereço
    if (bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("Erro no bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor UDP aguardando mensagens na porta %d...\n", SERVER_PORT);

    // Loop principal para receber e responder mensagens
    while (1) {
        bzero(buf, sizeof(buf));

        // Receber mensagem do cliente
        int len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_len);
        if (len < 0) {
            perror("Erro no recvfrom");
            continue;
        }

        printf("Mensagem recebida: %s\n", buf);

        // Enviar a mensagem de volta ao cliente
        if (sendto(sockfd, buf, len, 0, (struct sockaddr *)&client_addr, client_len) < 0) {
            perror("Erro ao enviar mensagem");
        } else {
            printf("Mensagem enviada de volta: %s\n", buf);
        }
    }

    // Fechar o socket
    close(sockfd);
    return 0;
}