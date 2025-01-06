#include "pipe_networking.h"
#include <signal.h>

int to_server;
int from_server;

static void sighandler(int signo)
{
    if (signo == SIGINT)
    {
        close(to_server);
        close(from_server);
        exit(0);
    }
}

int main()
{
    signal(SIGINT, sighandler);

    from_server = client_handshake(&to_server);

    while (1)
    {
        int num;
        int r = read(from_server, &num, sizeof(int));
        if (r == -1)
        {
            printf("[client] server disconnected\ ):n");
            break;
        }
        printf("[client] got: %d\n", num);
    }

    close(to_server);
    close(from_server);
    return 0;
}