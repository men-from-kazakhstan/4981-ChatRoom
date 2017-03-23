#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <QMainWindow>
#include <QMessageBox>

int sendMsg(int sockfd, const char *msg, size_t msgSize);
int getMsg(int sockfd, char *msg, size_t msgSize);
int createSocket(QMainWindow *parent, int *sck);

#endif // WRAPPERS_H
