#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 1024;

void error(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Erreur lors de la création de la socket");
    }

    struct sockaddr_in serv_addr;
    std::memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(4242); // Port IRC standard

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        error("Adresse IP invalide");
    }

    char buffer[BUFFER_SIZE];
    std::memset(buffer, 0, BUFFER_SIZE);
	sleep(20);
	std::cout << "Buffer: " << buffer << std::endl;
    recv(sockfd, buffer, BUFFER_SIZE, 0);
    std::cout << "Réponse du serveur après JOIN : " << buffer << std::endl;
    recv(sockfd, buffer, BUFFER_SIZE, 0);
    std::cout << "Réponse du serveur après l'envoi du message : " << buffer << std::endl;

    return 0;
}

