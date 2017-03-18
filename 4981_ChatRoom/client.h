// client.h

#ifndef CLIENT_H
#define CLIENT_H

#include "clientwindow.h"
#include "wrappers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
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
int createClientSocket(QWidget *parent);
int connectSocket(QWidget *parent);

bool validUsername(char *username, QWidget *parent);
bool validClientPort(char *port, QWidget *parent);
bool validIP(char *ip, QWidget *parent);
void concatUsername(char *username);
void concatPort(char *port);
void concatIP(char *ip);
void processUserMessage(const char *message, ClientWindow *main);
void updateHistory(std::string message);
void receiveMessage(ClientWindow *main);
void saveSession(QWidget * main);
void sendToServer(const char *msg, size_t msglen);

#endif // CLIENT_H
