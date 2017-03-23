/****************************************************************
 * This file contains all fucntions that are wrapper functions
 * for socket api calls
 ***************************************************************/

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
int sendMsg(int sockfd, const char *msg, size_t msgSize)
{
    int bytesSent;
    if ((bytesSent = send(sockfd, msg, msgSize, 0)) < 0)
    {
        fprintf(stderr, "send() failed with error: %s", strerror(errno));
        return -1;
    }

    return bytesSent;
}

/********************************************************
 *  Function:       getMsg(int sockfd, char *msg, size_t msgSize)
 *                      int sockfd: socket descriptor to read from
 *                      char *msg: message to read into
 *                      size_t msgSize: size of the message to read
 *
 *  Returns:        Number of bytes read or -1 if recv() failed
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 15 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Wraps the recv() call into a function which performs error checking
 *******************************************************/
int getMsg(int sockfd, char *msg, size_t msgSize)
{
    int bytesRead;
    if ((bytesRead = recv(sockfd, msg, msgSize, 0)) < 0)
    {
        fprintf(stderr, "recv() failed with error: %s", strerror(errno));
        return -1;
    }
    return bytesRead;
}

/********************************************************
 *  Function:       int createSocket(QMainWindow *parent, int *sck)
 *                      QWidget *parent  -  the current window in use
 *                      int *sck  -  location where socket will be saved to
 *
 *  Return:         Return 1 on success and 0 on failure
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 17 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Responsible for creating a socket
 *******************************************************/
int createSocket(QMainWindow *parent, int *sck)
{
    // create the TCP socket and error check
    if ((*sck = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return 0;
    }

    return 1;
}
