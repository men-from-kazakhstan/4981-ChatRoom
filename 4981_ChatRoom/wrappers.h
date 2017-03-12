#ifndef WRAPPERS_H
#define WRAPPERS_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>

/********************************************************
 *  Function:       sendMsg(int sockfd, char *msg, size_t msgSize)
 *                      int sockfd: socket descriptor to send to
 *                      char *msg: message to be sent out
 *                      size_t msgSize: size of the message to send
 *
 *  Returns:        Number of bytes sent or -1 if send() failed
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Wraps the send() call into a function which performs error checking
 *******************************************************/
int sendMsg(int sockfd, char *msg, size_t msgSize);


#endif // WRAPPERS_H
