#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 4249

// create a socket dgram with addr
int makeDgramSocket();

// send a message to dest_addr
int sendMessage(int sock, char *dest_addr, char *message, size_t msize);

// receive a message from address
int recvMessage(int sock, char *from_addr, char *buf, size_t bsize);

#endif // !_SOCKET_H_
