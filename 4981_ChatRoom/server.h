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

int setupServerSocket(QWidget* parent);
bool validServerPort(QString port, QWidget *parent);
int monitorConnections(QWidget* parent);

#endif // SERVER_H
