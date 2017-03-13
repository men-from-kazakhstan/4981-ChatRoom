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
 *  Function:       monitorSockets(int *clients, int numClients, fd_set *rset)
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
void monitorSockets(int *clients, int numClients);

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

/********************************************************
 *  Function:       checkClients(int numClients, fd_set *rset, int *clients, fd_set *allset)
 *                      int numClients: total number of clients
 *                      fd_set *rset: pointer to the set containing ready client descriptors
 *                      int *clients: array of client socket descriptors
 *                      fd_set *allset: pointer to the set containing all client descriptors
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 12 2017
 *
 *  Modified:
 *
 *  Desc:
 *      This loops through all possible clients in order to determine if they are set. If they are,
 *      it extracts the message written to them, before passing it on to the determine recipients
 *      state. It also handles closing the socket, if that was the client request.
 *******************************************************/
void checkClients(int numClients, fd_set *rset, int *clients, fd_set *allset);

/********************************************************
 *  Function:       determineRecepients(const char *message, int senderSocket, int numClients, int *clients)
 *                      const char *message: the message to send
 *                      int senderSocket: the fileDescriptor value for the message sender
 *                      int numClients: total number of clients
 *                      int *clients: array of client socket descriptors
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 12 2017
 *
 *  Modified:
 *
 *  Desc:
 *      This loops through all possible clients in order to determine if they exist, and aren't the
 *      original sender. If they meet these criteria, it then echoes the message to them using the
 *      sendMsg() function
 *******************************************************/
void determineRecepients(const char *message, int senderSocket, int numClients, int *clients);

#endif // SERVER_H
