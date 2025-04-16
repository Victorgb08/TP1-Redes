#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SERVER_PORT 54321
#define MAX_LINE 256

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

    // Criar o socket
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Erro ao criar o socket");
        return 1;
    }

    // Conectar ao servidor
    if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("Erro ao conectar ao servidor");
        close(s);
        return 1;
    }

    // Loop principal: enviar e receber mensagens
    while (fgets(buf, sizeof(buf), stdin)) {
        buf[MAX_LINE - 1] = '\0'; // Garantir que a string seja terminada
        len = strlen(buf) + 1;
        send(s, buf, len, 0);

        // Receber resposta do servidor
        bzero(buf, sizeof(buf));
        if (recv(s, buf, sizeof(buf), 0) > 0) {
            printf("Resposta do servidor: %s\n", buf);
        }
    }

    // Fechar o socket
    close(s);
    return 0;
}