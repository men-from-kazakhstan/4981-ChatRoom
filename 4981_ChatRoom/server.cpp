/****************************************************************
 * This file contains all fucntions that deal with the server side
 * operations
 ***************************************************************/

#include "server.h"
#include "serverwindow.h"
#include "wrappers.h"
#include "thread"
#include <map>

#include <QMessageBox>

struct sockaddr_in serverAddr;
int srv_socket;
std::map<int, std::string> clientMap;

/********************************************************
 *  Function:       int setupServerSocket(QWidget* parent)
 *
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:         Return 1 on success and 0 on failure
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
int setupServerSocket(ServerWindow *parent)
{
    // create the TCP socket and error check
    if (!createSocket(parent, &srv_socket))
    {
        return 0;
    }
    else
    {
        printf("%s\n", "\tServer: Socket Created");
    }

    // set socket option to reuse the address and error check
    if (!setSocketOptions(parent))
    {
        return 0;
    }
    else
    {
        printf("%s\n", "\tServer: Set socket options");
    }

    // bind the socket and error check
    if (!bindSocket(parent))
    {
        return 0;
    }
    else
    {
        printf("%s\n", "\tServer: Socket bind successful");
    }

    // start listening to the socket and error check
    if (!listenSocket(parent))
    {
        return 0;
    }
    else
    {
        printf("%s\n", "\tServer: Socket listen successful");
    }

    // go to monitor connections function
    std::thread reading(monitorConnections, parent);
    reading.detach();

    return 1;
}

/********************************************************
 *  Function:       int setSocketOptions(ServerWindow *parent)
 *
 *                      ServerWindow *parent  -  the current window in use
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
 *      Responsible for setting the socket option to reuse
 *      the same address
 *******************************************************/
int setSocketOptions(ServerWindow *parent)
{
    int arg = 1;

    // set socket option to reuse the address and error check
    if (setsockopt(srv_socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return 0;
    }

    return 1;
}


/********************************************************
 *  Function:       int bindSocket(ServerWindow *parent)
 *
 *                      ServerWindow *parent  -  the current window in use
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
 *      Responsible for binding the socket
 *******************************************************/
int bindSocket(ServerWindow *parent)
{
    // set family to IPv4
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // use any address trying to connect

    // bind the socket and error check
    if (bind(srv_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        QMessageBox::information(parent, "Error", strerror(errno));
        return 0;
    }

    return 1;
}


/********************************************************
 *  Function:       int listenSocket(ServerWindow *parent)
 *
 *                      ServerWindow *parent  -  the current window in use
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
 *      Responsible for setting the socket to listen for
 *      new connections
 *******************************************************/
int listenSocket(ServerWindow *parent)
{
    // start listening to the socket and error check
    if (listen(srv_socket, LISTENQ) < 0)
    {
        QMessageBox::information(parent, "Error", strerror(errno));
        return 0;
    }

    return 1;
}

/********************************************************
 *  Function:       int monitorConnections(QWidget* parent)
 *
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:         Return 1 on success and 0 on failure
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
int monitorConnections(ServerWindow *parent)
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
    while (true)
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

        // check for new client connections
        if (FD_ISSET(srv_socket, &rset))
        {
            client_len = sizeof(client_addr);

            // accept a new connection and error check
            if ((new_sd = accept(srv_socket, (struct sockaddr *)&client_addr, &client_len)) < 0)
            {
                QMessageBox::information(parent, "Error",  strerror(errno));
                return 0;
            }
            else
            {
                printf("%s\n", "\tServer: Client accepted");
                parent->updateClients(inet_ntoa(client_addr.sin_addr)); //update client list on server
                // add client socket and address to a map
                clientMap.insert(std::pair<int, std::string>(new_sd, inet_ntoa(client_addr.sin_addr)));
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
        checkClients(maxi, &rset, client, &allset, parent);
    }
    return 1;
}


/********************************************************
 *  Function:       bool validServerPort(QString port, QWidget *parent)
 *
 *                      QString port     -  port the validate
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:         Returns True on success and False on failure
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
    if (strlen(port) == 0)
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
 *  Modified:       Alex Zielinski ~ March 20 2017
 *
 *  Desc:
 *      This loops through all possible clients in order to determine if they are set. If they are,
 *      it extracts the message written to them, before passing it on to the determine recipients
 *      state. It also handles closing the socket, if that was the client request.
 *******************************************************/
void checkClients(int numClients, fd_set *rset, int *clients, fd_set *allset, ServerWindow *parent)
{
    char msg[BUFLEN];
    int sockfd;
    int bytesRead;

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

            //read message
            bytesRead = getMsg(sockfd, msg, BUFLEN);

            //close request received
            if (bytesRead == 0)
            {
                closeSocket(sockfd, allset, clients, i);
                parent->removeClient(clientMap.find(sockfd)->second.c_str());
                clientMap.erase(sockfd); // delete client from map
                continue;
            }

            //determine who should get the message
            determineRecepients(msg,sockfd,numClients,clients);
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
    char msg[BUFLEN];
    sprintf(msg, "Client %d has disconnected", sck);

    close(sck);
    FD_CLR(sck, allset);
    clients[index] = -1;
}
