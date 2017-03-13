#include "wrappers.h"

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
int sendMsg(int sockfd, const char *msg, size_t msgSize) {
    int bytesSent;
    if ((bytesSent = send(sockfd, msg, msgSize, 0)) < 0) {
        fprintf(stderr, "send() failed with error: %s", strerror(errno));
        return -1;
    }

    return bytesSent;
}
