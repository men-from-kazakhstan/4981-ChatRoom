/****************************************************************
 * This file contains all fucntions that deal with the server side
 * operations
 ***************************************************************/

#include "server.h"
#include "serverwindow.h"
#include "wrappers.h"

#include <QMessageBox>

struct sockaddr_in serverAddr;
int srv_socket;


/********************************************************
 *  Function:       int setupServerSocket(QWidget* parent)
 *
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:        return 0 on success and -1 on failure
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Responsible for socket creation. It creates the socket, sets
 *      the socket options to allow reusing the same address, binds
 *      the socket and starts listening to the socket
 *******************************************************/
int setupServerSocket(QWidget* parent)
{
    //socklen_t size;
    int arg = 1;

    // create the TCP socket and error check
    if((srv_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return -1;
    }
    else
    {
        printf("%s\n", "\tServer: Socket Created");
    }

    // set socket option to reuse the address and error check
    if(setsockopt(srv_socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return -1;
    }
    else
    {
        printf("%s\n", "\tServer: Set socket options");
    }

    // set family to IPv4
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // use any address trying to connect

    // bind the socket and error check
    if(bind(srv_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        QMessageBox::information(parent, "Error", strerror(errno));
        return -1;
    }
    else
    {
        printf("%s\n", "\tServer: Socket bind successful");
    }

    // start listening to the socket and error check
    if(listen(srv_socket, LISTENQ) < 0)
    {
        QMessageBox::information(parent, "Error", strerror(errno));
        return -1;
    }

    // go to monitor connections function
    monitorConnections(parent);

    return 0;
}


/********************************************************
 *  Function:       int monitorConnections(QWidget* parent)
 *
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:        return 0 on success and -1 on failure
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:       March 15 2017 - Robert Arendac
 *                      Fixed a couple bugs, mostly due to indexing and scope issues.
 *                      Also added the checkClients() function.
 *
 *  Desc:
 *      Responsible for monitoring all the clients that
 *      connect to the server via the select() call
 *******************************************************/
int monitorConnections(QWidget* parent)
{
    struct sockaddr_in client_addr;
    int nready, maxfd, maxi, new_sd, client[FD_SETSIZE];
    socklen_t client_len;
    fd_set rset, allset;
    int i;

    maxfd = srv_socket;
    maxi = -1;

    for(i = 0; i < FD_SETSIZE; i++)
    {
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(srv_socket, &allset);
    while(true)
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

        // check for new client connections
        if(FD_ISSET(srv_socket, &rset))
        {
            client_len = sizeof(client_addr);

            // accept a new connection and error check
            if((new_sd = accept(srv_socket, (struct sockaddr *)&client_addr, &client_len)) < 0)
            {
                QMessageBox::information(parent, "Error",  strerror(errno));
                return -1;
            }
            else
            {
                printf("%s\n", "\tServer: Client accepted");
            }

            printf(" Remote Address:  %s\n", inet_ntoa(client_addr.sin_addr));

            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = new_sd;	// save descriptor
                    break;
                }
            }

            if (i == FD_SETSIZE)
            {
                printf ("Too many clients\n");
                exit(1);
            }

            FD_SET (new_sd, &allset);     // add new descriptor to set

            if (new_sd > maxfd)
                maxfd = new_sd;	// for select

            if (i > maxi)
                maxi = i;	// new max index in client[] array

            if (--nready <= 0)
                continue;	// no more readable descriptors

        }
        checkClients(maxi, &rset, client, &allset);
    }
    return 0;
}


/********************************************************
 *  Function:       bool validServerPort(QString port, QWidget *parent)
 *
 *                      QString port     -  port the validate
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:        returns True on success and False on failure
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Responsible for validating the the port the user
 *******************************************************/
bool validServerPort(char *port, QWidget *parent)
{
    int tmpPort;

    // check if nothing was entered and display error if so
    if(strlen(port) == 0)
    {
        QMessageBox::information(parent, "Error", "Error: You must enter a port number");
        return false;
    }

    tmpPort = atoi(port);  // convert char* to int


    // assign port
    serverAddr.sin_port = htons(tmpPort);
    return true;
}


/********************************************************
 *  Function:       monitorSockets(int *clients, int numClients, fd_set *rset)
 *                      int *clients: array of client socket descriptors
 *                      int numClients: total number of clients in the clients array
 *                      fd_set *rset: pointer to the set containing the ready client descriptors
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Will go through each socket and determine if one is ready to send
 *      data to the server.  Once all data is received, it will get ready
 *      to echo the message to the appropriate clients.  Will close sockets
 *      if nothing is read.
 *******************************************************/
/* Don't think we need this...
void monitorSockets(int *clients, int numClients, fd_set *rset, fd_set *allset)
{

    //Make select call

    //check for new connection

    //call checkClients (do this regardless of if a new client has connected or not.

}
*/

/********************************************************
 *  Function:       checkClients(int numClients, fd_set *rset, int *clients, fd_set *allset)
 *                      int numClients: total number of clients
 *                      fd_set *rset: pointer to the set containing ready client descriptors
 *                      int *clients: array of client socket descriptors
 *                      fd_set *allset: pointer to the set containing all client descriptors
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 12 2017
 *
 *  Modified:
 *
 *  Desc:
 *      This loops through all possible clients in order to determine if they are set. If they are,
 *      it extracts the message written to them, before passing it on to the determine recipients
 *      state. It also handles closing the socket, if that was the client request.
 *******************************************************/
void checkClients(int numClients, fd_set *rset, int *clients, fd_set *allset)
{
    char msg[BUFLEN];
    int sockfd;
    int bytesRead;
    int bytesToRead;

    //loop through all possible clients
    for (int i = 0; i <= numClients; i++)
    {
        //check to see if current client exists
        if ((sockfd = clients[i]) < 0)
        {
            continue;
        }
        //check to see if current client is signaled
        if (FD_ISSET(sockfd,rset))
        {
            bytesToRead = BUFLEN;

            //read message
            bytesRead = getMsg(sockfd,msg,BUFLEN);

            //determine who should get the message
            determineRecepients(msg,sockfd,numClients,clients);

            //close request received
            if (bytesRead == 0)
            {
                closeSocket(sockfd, allset, clients, i);
            }
        }
    }
}


/********************************************************
 *  Function:       determineRecepients(const char *message, int senderSocket, int numClients, int *clients)
 *                      const char *message: the message to send
 *                      int senderSocket: the fileDescriptor value for the message sender
 *                      int numClients: total number of clients
 *                      int *clients: array of client socket descriptors
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 12 2017
 *
 *  Modified:
 *
 *  Desc:
 *      This loops through all possible clients in order to determine if they exist, and aren't the
 *      original sender. If they meet these criteria, it then echoes the message to them using the
 *      sendMsg() function
 *******************************************************/
void determineRecepients(const char *message, int senderSocket, int numClients, int *clients)
{
    int sockfd;
    //loop through all possible clients.
    for (int i = 0; i <= numClients; i++)
    {
        //sheck client slot
        sockfd = clients[i];
        // If client doesn't exist, or is the original sender
        if (sockfd < 0 || sockfd == senderSocket)
        {
            continue;
        }
        //send() wrapper function.
        sendMsg(sockfd,message,BUFLEN);
    }
}


/********************************************************
 *  Function:       closeSocket(int sck, fd_set *allset, int *clients, int index)
 *                      int sck: the socket to close
 *                      fd_set *allset: pointer to the set containing all client descriptors
 *                      int *clients: array of client socket descriptors
 *                      int index: index where the socket to close is in the clients array
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      A message box will pop up notifying the user that a client has disconnected, should
 *      be changed so that the client list is updated instead.  Will then close the socket
 *******************************************************/
void closeSocket(int sck, fd_set *allset, int *clients, int index)
{
    QMessageBox msgbox;
    char msg[BUFLEN];
    sprintf(msg, "Client %d has disconnected", sck);
    msgbox.setText(msg);
    msgbox.exec();

    close(sck);
    FD_CLR(sck, allset);
    clients[index] = -1;
}
