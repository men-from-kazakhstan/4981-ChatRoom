#include <QMessageBox>
#include "server.h"
#include "serverwindow.h"
#include "wrappers.h"

/*
 * Read sockets
 * update client list
 * close socket
 *
 * get message
 * determine ignore list
 * send message
 */

/* Read the sockets that are ready to send data */
void monitorSockets(int *clients, int numClients, fd_set *rset, fd_set *allset) {

    //Make select call

    //check for new connection

    //call checkClients (do this regardless of if a new client has connected or not.

}

/*
 *  Check each client to see if it has a message.
 */
void checkClients(int numClients, fd_set *rset, int *clients, fd_set *allset) {

    char msg[BUFLEN];
    char *pmsg;
    int sockfd;
    int bytesRead;
    int bytesToRead;
    //loop through all possible clients
    for (int i = 0; i < numClients; i++) {
        //check to see if current client exists
        if ((sockfd = clients[i]) < 0) {
            continue;
        }
        //check to see if current client is signaled
        if (FD_ISSET(sockfd,rset)) {
            bytesToRead = BUFLEN;
            pmsg = msg;
            //read message
            while ((bytesRead = read(sockfd,pmsg,bytesToRead)) > 0) {
                pmsg += bytesRead;
                bytesToRead -= bytesRead;
            }
            //determine who should get the message
            determineRecepients(msg,sockfd,numClients,clients);

            //close request received
            if (bytesRead == 0) {
                closeSocket(sockfd, allset, clients, i);
            }
        }
    }
}

/*
 * Method that ensures a client doesn't self-echo
 */
void determineRecepients(const char *message, int senderSocket, int numClients, int *clients) {
    int sockfd;
    //loop through all possible clients.
    for (int i = 0; i < numClients; i++) {
        //sheck client slot
        sockfd = clients[i];
        // If client doesn't exist, or is the original sender
        if (sockfd < 0 || sockfd == senderSocket) {
            continue;
        }
        //send() wrapper function.
        sendMsg(sockfd,message,BUFLEN);
    }
}

/* Notify user and then close a socket */
void closeSocket(int sck, fd_set *allset, int *clients, int index) {
    QMessageBox msgbox;
    char msg[BUFLEN];
    sprintf(msg, "Client %d has disconnected", sck);
    msgbox.setText(msg);
    msgbox.exec();

    close(sck);
    FD_CLR(sck, allset);
    clients[index] = -1;
}
