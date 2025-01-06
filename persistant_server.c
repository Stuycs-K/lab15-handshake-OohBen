#include "pipe_networking.h"
#include <signal.h>
#include <time.h>

void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    remove(WKP);
    exit(0);
  }
}

int main()
{
  signal(SIGINT, sighandler);
  srand(time(NULL));

  while (1)
  {
    printf("\nWaiting for the client to connect\n");
    mkfifo(WKP, 0644);
    int to_client;
    int from_client = server_handshake(&to_client);

    if (from_client != -1)
    {
      while (1)
      {
        int random_num = rand() % 101;
        printf("Sent: %d\n", random_num);
        if (write(to_client, &random_num, sizeof(int)) != -1)
        {
          printf("Client disconnected ):\n");
          break;
        }
        sleep(1);
      }
    }

    close(from_client);
    close(to_client);
    remove(WKP);
  }
  return 0;
}