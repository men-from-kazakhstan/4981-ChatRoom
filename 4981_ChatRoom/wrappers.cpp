#include "wrappers.h"

int sendMsg(int sockfd, char *msg, size_t msgSize) {
    int bytesSent;
    if ((bytesSent = send(sockfd, msg, msgSize, 0)) < 0) {
        fprintf(stderr, "send() failed with error: %s", strerror(errno));
        return -1;
    }

    return bytesSent;
}
