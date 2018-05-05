#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>

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
int main() {
  const int port_number = 5050;

  struct addrinfo hint;
  struct addrinfo *addrs;
  memset(&hint, 0, sizeof(struct addrinfo));
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  getaddrinfo("0.0.0.0", NULL, &hint, &addrs);

  printf("Create a socket...\n");
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  check_status(socket_fd >= 0, "Fail to create a socket");

  printf("Connect to a socket...\n");
  struct sockaddr_in local_addr;
  socklen_t sock_len;
  memcpy(&local_addr, addrs->ai_addr, addrs->ai_addrlen);
  local_addr.sin_port = htons(port_number);
  sock_len = sizeof(struct sockaddr_in);
  int ret =  connect(socket_fd, (struct sockaddr *)&local_addr, sock_len);
  check_status(ret >= 0, "Fail to connect a socket");

  printf("Send data...\n");
  const char *msg = "Hello world!";
  send(socket_fd, msg, strlen(msg), 0);

  printf("Shutdown client...\n");
  freeaddrinfo(addrs);
  close(socket_fd);

  return 0;
}
