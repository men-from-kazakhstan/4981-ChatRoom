#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>

int sendMsg(int sockfd, const char *msg, size_t msgSize);
int getMsg(int sockfd, char *msg, size_t msgSize);

#endif // WRAPPERS_H
