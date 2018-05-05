#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>
#include <netinet/in.h>

#define check_status(expr, msg)                                         \
  if (!(expr)) {                                                        \
    fprintf(stderr, "%s\n", msg);                                       \
    fprintf(stderr, " - errno # %d (%s)\n", errno, strerror(errno));    \
    fprintf(stderr, " - line # %d (file # %s)\n", __LINE__, __FILE__);  \
    exit(1);                                                            \
  }

//
// App entry point
//
int main()
{
  struct hostent* hostinfo;
  hostinfo = gethostbyname("www.google.co.uk");
  check_status(hostinfo, "Fail to get hostname");

  printf("Create a socket...\n");
  int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
  check_status(socket_fd >= 0, "Fail to create a socket");

  printf("Connect to a socket...\n");
  struct sockaddr_in in_addr;
  socklen_t sock_len;
  in_addr.sin_family = AF_INET;
  in_addr.sin_addr = *((struct in_addr *) hostinfo->h_addr);
  in_addr.sin_port = htons(80);
  sock_len = sizeof(struct sockaddr_in);
  int ret =  connect(socket_fd, (struct sockaddr *)&in_addr, sock_len);
  check_status(ret >= 0, "Fail to connect a socket");

  printf("Send data...\n");
  const char *msg = "GET /\n";
  send(socket_fd, msg, strlen(msg), 0);

  const int length = 500;
  char buffer[length];
  while (1) {
      int re = read(socket_fd, buffer, length);
      if (re == 0)
          break;

      fwrite(buffer, sizeof(char), re, stdout);
  }

  printf("\n\nShutdown client...\n");
  close(socket_fd);

  return 0;
}
