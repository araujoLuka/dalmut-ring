#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "libsocket.h"

#define MSG1	"Hello_Louis"
#define MSG2	"Hello_Lucas"
#define MAXMSG	512

#define HOST1   "192.168.1.7"
#define HOST2   "192.168.1.27"

static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

int main(int argc, char *argv[]) {
    int s = 0, r = 0;
    char message[MAXMSG];
	int sock;

    printf("Creating socket\n");
    sock = makeDgramSocket ();

	if (argc > 1 && !strcmp(argv[1], "server")) {
        while(keepRunning) {
            printf("%d: Sending message '%s' to %s\n", s, MSG1, HOST2);
            sendMessage(sock, HOST2, MSG1, strlen(MSG1)+1);
            
            printf("%d: Receiving message from %s\n", s, HOST2);
            recvMessage(sock, HOST2, message, MAXMSG);
            printf("%d: Received %s\n", s, message);
            
            sleep(5);
            s++;
        }
    }
	else {
        while(keepRunning) {
            printf("%d: Receiving message from %s\n", r, HOST1);
            recvMessage(sock, HOST1, message, MAXMSG);
            printf("%d: Received %s\n", r, message);

            printf("%d: Sending message '%s' to %s\n", r, MSG2, HOST1);
            sendMessage(sock, HOST1, "Hello_Lucas", strlen(MSG2)+1);
            
            sleep(5);
            r++;
        }
    }

    close(sock);
    return 0;
}
