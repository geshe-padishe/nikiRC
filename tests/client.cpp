#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Erreur lors de la création de la socket");
    }

    if (connect(sockfd, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0) {
        error("Erreur de connexion");
    }

    const char *joinChannelMessage = "JOIN #1\r\n";
    send(sockfd, joinChannelMessage, strlen(joinChannelMessage), 0);

    const char *sendMessage = "PRIVMSG #nouveau_canal :Salut, c'est mon message!\r\n";
    send(sockfd, sendMessage, strlen(sendMessage), 0);

    close(sockfd);
	return (0);
}
