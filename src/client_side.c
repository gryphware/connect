#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 5000

void chat(int newSocket);

int main() {

  int cliSocket;
  struct sockaddr_in serverAddress;
  cliSocket = socket(PF_INET, SOCK_STREAM, 0);
  if (cliSocket > 0) {
    printf("client's site is created!\n");
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_family = PF_INET;
    serverAddress.sin_port = htons(PORT);
    int status = connect(cliSocket, (struct sockaddr *)&serverAddress,
                         sizeof(serverAddress));
    if (status < 0) {
      perror("connect error!\n");
      exit(EXIT_FAILURE);
    }
    chat(cliSocket);
    close(cliSocket);
  }
    return EXIT_SUCCESS;
}

void chat(int newSocket) {
  char buffer[100];
  while (true) {
    printf("to server: ");
    fgets(buffer, sizeof(buffer), stdin);
    send(newSocket, buffer, sizeof(buffer), 0);
    recv(newSocket, buffer, sizeof(buffer), 0);
    printf("from server: %s\n", buffer);
    if (strcmp(buffer, "bye\n") == 0) {
        return;
    }
  }
}
