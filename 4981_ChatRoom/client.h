// client.h

#ifndef CLIENT_H
#define CLIENT_H

#include "clientwindow.h"
#include "wrappers.h"

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

#define BUFLEN 512
#define INPUTBUFF 32

/* struct that contains all client info */
struct ClientInfo{
    struct sockaddr_in cltAddr;
    int cltSock;
    char username[INPUTBUFF];
};

int setupClientSocket(QWidget *parent);

bool validUsername(char *username, QWidget *parent);
bool validClientPort(char *port, QWidget *parent);
bool validIP(char *ip, QWidget *parent);

void concatUsername(char *username);
void concatPort(char *port);
void concatIP(char *ip);
void getUserMessage(ClientWindow *cw, char *completeMsg, char *IP, char *username);
void formatMessage(const char *message, const char *IP, const char *username, char* dest);
void sendToServer(char *msg, size_t msglen);

#endif // CLIENT_H
