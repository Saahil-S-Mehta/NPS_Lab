
/*Client*/
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
int main(int argc,char *argv[])
{
  int create_socket;
  int bufsize = 1024, cont;
  char *buffer = malloc(bufsize);
  char fname[256];
  struct sockaddr_in address;
  if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
  printf("The Socket was created\n");
  address.sin_family = AF_INET;
  address.sin_port = htons(15001);
  inet_pton(AF_INET,argv[1],&address.sin_addr);
  if (connect(create_socket,(struct sockaddr *) &address, sizeof(address)) == 0)
  printf("The connection was accepted with the server %s...\n",argv[1]);
  printf("Enter The Filename to Request : "); scanf("%s",fname);
  send(create_socket, fname, sizeof(fname), 0);
  printf("Request Accepted... Receiving File...\n\n");
  char *new_fname = strcat(fname, "-copy");
  printf("The contents of file are copied into %s\n", new_fname);
  while((cont=recv(create_socket, buffer, bufsize, 0))>0) {
    int fd = open(new_fname, O_CREAT | O_RDWR);
    write(fd, buffer, cont);
    close(fd);
  }
  return close(create_socket);
}
