#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>

#define PORT 5000

void chat(int newSocket);

int main() {

    struct sockaddr_in serverAddress, newAddress;
    int serverSocket, newSocket, s;
    socklen_t size;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (serverSocket > 0) {
      printf("this server's socket is created\n");
      serverAddress.sin_family = PF_INET;
      serverAddress.sin_port = htons(PORT);
      serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
      s = bind(serverSocket, (struct sockaddr *)&serverAddress,
               sizeof(serverAddress));
      if (s == 0) {
        printf("bind success\n");
        listen(serverSocket, 1);
        size = sizeof(newAddress);
        printf("ready\n");
        newSocket = accept(serverSocket, (struct sockaddr *)&newAddress, &size);
        if (newSocket > 0) {
          printf("acpect!\n");
          chat(newSocket);
          close(newSocket);
        }
      }
    }
    return EXIT_SUCCESS;
}

void chat(int newSocket) {
  char buffer[100];
  while (true) {
    recv(newSocket, buffer, sizeof(buffer), 0);
    printf("from client: %s\n", buffer);
    if (strcmp(buffer, "bye\n") == 0) {
        return;
    }
    printf("to client: ");
    fgets(buffer, sizeof(buffer), stdin);
    send(newSocket, buffer, sizeof(buffer), 0);
  }
}
