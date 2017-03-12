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


void readSockets(int *clients, int numClients, fd_set *rset) {
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

            while ((bytesRead = read(curSck, pmsg, bytesToRead)) > 0) {
                pmsg += bytesRead;
                bytesToRead -= bytesRead;
            }

            // TODO: MATT GOERWELL
            // Extract ID
            // Echo


        }
    }
}

void closeSocket(ServerWindow *sw, int sck, fd_set *allset, int *clients) {

}
