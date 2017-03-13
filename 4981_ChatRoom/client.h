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

struct ClientInfo{
    struct sockaddr_in cltAddr;
    int cltSock;
    char username[INPUTBUFF];
};

int setupClientSocket(QWidget *parent);

bool validUsername(QString username, QWidget *parent);
bool validClientPort(QString port, QWidget *parent);
bool validIP(QString ip, QWidget *parent);

void concatUsername(char *username);
void concatPort(char *port);
void concatIP(char *ip);

#endif // CLIENT_H
