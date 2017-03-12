#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>

#define LISTENQ 5   // Queue for the listen call
#define BUFLEN 512  // Maximum size of a message

/********************************************************
 *  Function:       readSockets(int *clients, int numClients, fd_set *rset)
 *                      int *clients: array of client socket descriptors
 *                      int numClients: total number of clients in the clients array
 *                      fd_set *rset: pointer to the set containing the client descriptors
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Will go through each socket and determine if one is ready to send
 *      data to the server.  Once all data is received, it will get ready
 *      to echo the message to the appropriate clients.  Will close sockets
 *      if nothing is read.
 *******************************************************/
void readSockets(int *clients, int numClients);


#endif // SERVER_H
