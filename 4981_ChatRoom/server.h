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
 *                      fd_set *rset: pointer to the set containing the ready client descriptors
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

/********************************************************
 *  Function:       closeSocket(int sck, fd_set *allset, int *clients, int index)
 *                      int sck: the socket to close
 *                      fd_set *allset: pointer to the set containing all client descriptors
 *                      int *clients: array of client socket descriptors
 *                      int index: index where the socket to close is in the clients array
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      A message box will pop up notifying the user that a client has disconnected, should
 *      be changed so that the client list is updated instead.  Will then close the socket
 *******************************************************/
void closeSocket(int sck, fd_set *allset, int *clients, int index);

#endif // SERVER_H
