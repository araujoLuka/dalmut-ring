#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "essential.h"

#define SERVER	"/tmp/serversocket"
#define MAXMSG	512

int make_dgram_socket(char *dest_addr) 
{
	struct sockaddr_in dest;
	int sock;
	size_t size;

	/* Create the socket. */
	sock = socket (PF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror ("socket");
		exit (EXIT_FAILURE);
	}

	/* Bind a name to the socket. */
	dest.sin_family = AF_INET;
	inet_aton(dest_addr, &dest.sin_addr);
	dest.sin_port = htons(2253);

	return sock;
}

int main (void)
{
	int sock;
	char message[MAXMSG];
	char *test = "Hello, Louis\n";
	struct sockaddr_in dest;
	size_t size;
	int nbytes;

	/* Make the socket, then loop endlessly. */
	sock = make_dgram_socket("10.254.225.29");

	size = sizeof(dest);
	nbytes = sendto(sock, test, strlen(test)+1, 0, (struct sockaddr *) &dest, size);

	if (nbytes < 0)
	{
		perror ("failure to send hello");
		exit (EXIT_FAILURE);
	}

	return 0;

	while (1)
	{
	    /* Wait for a datagram. */
	    size = sizeof (dest);
	    nbytes = recvfrom (sock, message, MAXMSG, 0,
	                       (struct sockaddr *) & dest, (unsigned int *)&size);
	    if (nbytes < 0)
	    {
	        perror ("recfrom (server)");
	        exit (EXIT_FAILURE);
	    }

	    /* Give a diagnostic message. */
	    fprintf (stderr, "Server: got message: %s\n", message);

	    /* Bounce the message back to the sender. */
	    nbytes = sendto (sock, message, nbytes, 0,
	                     (struct sockaddr *) & dest, size);
	    if (nbytes < 0)
		{
		perror ("sendto (server)");
		exit (EXIT_FAILURE);
		}
	}
}

