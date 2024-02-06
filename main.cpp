#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_EVENTS 10
const int BUFFER_SIZE = 1024;

void error(const char *msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

int main() {
	int tcpsocket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serv_addr;
	
	if (tcpsocket < 0)
		error("Unable to create socket\n");
	std::memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(6667); // Port IRC standard
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
		error("Adresse IP invalide");
	if (connect(tcpsocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
		error("Erreur de connexion");
	if (bind(tcpsocket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
		error("Bindig Error");
	if (listen(tcpsocket, 100))
		error("Listen Error");
	struct epoll_event ev, events[MAX_EVENTS];
	int listen_sock, conn_sock, nfds, epollfd;
	
	/* Code to set up listening socket, 'listen_sock',
	   (socket(), bind(), listen()) omitted */
	
	epollfd = epoll_create1(0);
	if (epollfd == -1) {
		perror("epoll_create1");
		exit(EXIT_FAILURE);
	}
	ev.events = EPOLLIN;
	ev.data.fd = tcpsocket;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, tcpsocket, &ev) == -1) {
		perror("epoll_ctl: listen_sock");
		exit(EXIT_FAILURE);
	}
	for (;;) {
		nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		if (nfds == -1) {
			perror("epoll_wait");
			exit(EXIT_FAILURE);
		}
		for (int n = 0; n < nfds; ++n) {
			if (events[n].data.fd == tcpsocket) {
				conn_sock = accept(tcpsocket, NULL, NULL);
				if (conn_sock == -1) {
					perror("accept");
					exit(EXIT_FAILURE);
				}
				fcntl(conn_sock, F_SETFL, O_NONBLOCK);
				//setnonblocking(conn_sock); set socket non-blocking
				ev.events = EPOLLIN | EPOLLET;
				ev.data.fd = conn_sock;
				if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
					perror("epoll_ctl: conn_sock");
					exit(EXIT_FAILURE);
				}
			} else {
				do_use_fd(events[n].data.fd);
			}
		}
	}
	char buffer[BUFFER_SIZE];
	std::memset(buffer, 0, BUFFER_SIZE);
	
	// Envoyer un message au serveur IRC pour créer le canal
	//const char *createChannelMessage = "JOIN #nouveau_canal\r\n";
	//send(tcpsocket, createChannelMessage, strlen(createChannelMessage), 0);
	
//	recv(tcpsocket, buffer, BUFFER_SIZE, 0);
//	std::cout << "Réponse du serveur : " << buffer << std::endl;
	// Recevoir et afficher la réponse du serveur
	
	// Fermer la connexion
	close(tcpsocket);
	
	return 0;
}
