// server.h

#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QMessageBox>
#include <errno.h>

#define INPUTBUFF 32
#define LISTENQ 5   // Queue for the listen call
#define BUFLEN 512  // Maximum size of a message

int setupServerSocket(QWidget* parent);
int monitorConnections(QWidget* parent);
int createServerSocket(QWidget *parent);
int setSocketOptions(QWidget *parent);
int bindSocket(QWidget *parent);
int listenSocket(QWidget *parent);

//------- make function take in a char* instead of QString
bool validServerPort(char *port, QWidget *parent);
//-------

void monitorSockets(int *clients, int numClients);
void closeSocket(int sck, fd_set *allset, int *clients, int index);
void checkClients(int numClients, fd_set *rset, int *clients, fd_set *allset);
void determineRecepients(const char *message, int senderSocket, int numClients, int *clients);

#endif // SERVER_H
