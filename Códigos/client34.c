#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT 54321 // Porta correta conforme especificação
#define MAX_LINE 256      // Tamanho máximo do buffer

int main(int argc, char *argv[]) {
    struct hostent *hp;
    struct sockaddr_in sin;
    char *host;
    char buf[MAX_LINE];
    int s;
    int len;

    // Verificar se o endereço do servidor foi passado como argumento
    if (argc == 2) {
        host = argv[1];
    } else {
        fprintf(stderr, "Uso: %s <endereço do servidor>\n", argv[0]);
        return 1;
    }

    // Traduzir o nome do host para o endereço IP
    hp = gethostbyname(host);
    if (!hp) {
        fprintf(stderr, "Erro: host desconhecido: %s\n", host);
        return 1;
    }

    // Configurar o endereço do servidor
    bzero((char *)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    bcopy(hp->h_addr, (char *)&sin.sin_addr, hp->h_length);
    sin.sin_port = htons(SERVER_PORT);

    // Criar o socket UDP
    if ((s = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Erro ao criar o socket");
        return 1;
    }

    printf("Conectado ao servidor UDP. Digite mensagens (CTRL+D para sair):\n");

    // Loop principal: enviar e receber mensagens
    while (fgets(buf, sizeof(buf), stdin)) {
        buf[MAX_LINE - 1] = '\0'; // Garantir que a string seja terminada
        len = strlen(buf) + 1;

        // Enviar mensagem ao servidor
        if (sendto(s, buf, len, 0, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
            perror("Erro ao enviar mensagem");
            break;
        }

        // Receber resposta do servidor
        bzero(buf, sizeof(buf));
        if ((len = recvfrom(s, buf, sizeof(buf), 0, NULL, NULL)) > 0) {
            printf("Servidor: %s\n", buf);
        } else {
            perror("Erro ao receber mensagem");
            break;
        }
    }

    // Fechar o socket
    close(s);
    return 0;
}