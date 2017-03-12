#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QMessageBox>
#include <errno.h>

#define INPUTBUFF 32

extern struct sockaddr_in serverAddr, newCltAddr;
extern int srv_socket;
extern char srvPort[INPUTBUFF];

int setupServerSocket(QWidget* parent, int *sock, sockaddr_in srvAddr, sockaddr_in newAddr, char port[INPUTBUFF]);

#endif // SERVER_H
