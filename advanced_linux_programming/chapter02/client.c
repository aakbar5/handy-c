// Listing 2.4 (client.c) Part of a Network Client Program

#include <stdio.h>
#include <stdlib.h>

//
// App entry point
//
int main()
{
  char *server = getenv("SERVER_NAME");
  if (!server) {
    server = "default.server.name";
  }

  printf("Server Name: %s\n", server);
  return 0;
}
