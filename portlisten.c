#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

//define how many PORTS to be scanned. (a computer has 65535 ports avaliable)
#define MAX_PORT 8080

int main(int argc, char** argv){
  unsigned int openPortsNumber = 0;

  struct sockaddr_in listener;

  if(argc == 1){
    listener.sin_addr.s_addr = INADDR_ANY;
  }else{
    listener.sin_addr.s_addr = inet_addr(argv[1]);
  }
  if(listener.sin_addr.s_addr == INADDR_NONE){
    fprintf(stderr, "Erro cant get the address.");
    return -1;
  }

  for(int port = 1; port <= MAX_PORT; port++){
  int sd = socket(AF_INET, SOCK_STREAM, 0);
    listener.sin_family = AF_INET;
    listener.sin_port = htons(port);
    int retconnect = connect(sd, (struct sockaddr*)&listener, sizeof(listener));
    if(retconnect < 0){
      printf("[%d]PORT CLOSED\n", port);
    }else{
      printf("[%d]PORT OPEN\n", port);
      openPortsNumber++;
    }
  close(sd);
  }
  printf("%d ports checked\n[%d]TOTAL PORTS OPEN\n", MAX_PORT, openPortsNumber);
  return 0;
}
