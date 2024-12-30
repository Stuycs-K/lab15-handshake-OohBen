#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
    int from_client;
    mkfifo(WKP, 0666);
    printf("[server] created WKP\n");
    from_client = open(WKP, O_RDONLY);
    printf("[server] opened WKP\n");
    remove(WKP);
    printf("[server] removed WKP\n");  
    return from_client;
}


/*=========================
  server_handshake 
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client;
  char buffer[HANDSHAKE_BUFFER_SIZE];
  from_client = server_setup();
  read(from_client, buffer, HANDSHAKE_BUFFER_SIZE);
  printf("[server] received private pipe name: %s\n", buffer);
  *to_client = open(buffer, O_WRONLY);
  printf("[server] opened private pipe\n");
  int rand_num = rand();
  write(*to_client, &rand_num, sizeof(int));
  printf("[server] wrote to private pipe\n");
  int response;
  read(from_client, &response, sizeof(int));
  printf("[server] received response: %d\n", response);
  if (response != rand_num+1) {
    printf("[server] handshake failed\n");
    return -1;
  }
  printf("[server] handshake successful\n");
  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}


