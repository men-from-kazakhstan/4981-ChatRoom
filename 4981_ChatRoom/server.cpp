#include <QMessageBox>
#include "server.h"
#include "serverwindow.h"

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
void readSockets(int *clients, int numClients, fd_set *rset, fd_set *allset) {
    int curSck;
    char msg[BUFLEN];
    char *pmsg;
    int bytesRead;
    int bytesToRead;

    for (int i = 0; i <= numClients; i++) {

        //Check if client is connected
        if ((curSck = clients[i]) < 0) {
            continue;
        }

        if (FD_ISSET(curSck, rset)) {
            bytesToRead = BUFLEN;
            pmsg = msg;

            while (bytesToRead > 0) {
                if ((bytesRead = read(curSck, pmsg, bytesToRead)) > 0) {
                    pmsg += bytesRead;
                    bytesToRead -= bytesRead;
                }
            }

            // TODO: MATT GOERWELL
            // Extract ID
            // Echo

            if (bytesRead == 0) {
                closeSocket(curSck, allset, clients, i);
            }
        }
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
