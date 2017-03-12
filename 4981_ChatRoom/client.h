#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QMessageBox>
#include <errno.h>

#define INPUTBUFF 32

extern struct sockaddr_in clientAddr;
extern int clt_socket;
extern char cltUsername[INPUTBUFF];
extern char cltPort[INPUTBUFF];
extern char cltIP[INPUTBUFF];

int setupClientSocket(QWidget *parent, int *sock, sockaddr_in cltAddr, char port[INPUTBUFF], char ip[INPUTBUFF]);

bool validUsername(QString username, QWidget *parent);
bool validPort(QString port, QWidget *parent);
bool validIP(QString ip, QWidget *parent);

#endif // CLIENT_H
