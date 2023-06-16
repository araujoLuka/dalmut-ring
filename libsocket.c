#include "libsocket.h"

int makeDgramSocket() {
	struct sockaddr_in name;
	int sock;
	size_t size;

	/* Create the socket. */
	sock = socket (PF_INET, SOCK_DGRAM, 0);
	if (sock < 0) {
		perror ("socket");
		exit (EXIT_FAILURE);
	}

	/* Bind a name to the socket. */
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = INADDR_ANY;
	name.sin_port = PORT;

	size = sizeof(name);

	if (bind (sock, (struct sockaddr *) &name, size) < 0) {
		perror ("bind");
		exit (EXIT_FAILURE);
	}

	return sock;
}

int sendMessage(int sock, char *dest_addr, char *message, size_t msize) {
	struct sockaddr_in dest;
	size_t size;
	int nbytes;

    dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(dest_addr);
	dest.sin_port = PORT;
    
	size = sizeof (dest);
	nbytes = sendto(sock, message, msize, 0, 
                 (struct sockaddr *) &dest, size);

	if (nbytes < 0)
	{
		perror ("failure to send hello");
		exit (EXIT_FAILURE);
	}

    printf("nbytes: %d\n", nbytes);

	return 0;
}

int recvMessage(int sock, char *from_addr, char *buf, size_t bsize) {
	char message[bsize];
	struct sockaddr_in from;
	size_t size;
	int nbytes;

	size = sizeof (from);

	nbytes = recvfrom(sock, message, strlen(message)+1, 0,
				   (struct sockaddr *) &from, (unsigned int *)&size);

	if (nbytes < 0)
	{
		perror ("failure to send hello");
		exit (EXIT_FAILURE);
	}

    printf("nbytes: %d\n", nbytes);

	fprintf (stderr, "Server: got message: %s\n", message);

    strcpy(buf, message);

	return 0;
}
