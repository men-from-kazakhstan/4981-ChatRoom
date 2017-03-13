/****************************************************************
 * This file contains all fucntions that deal with the client side
 * operations
 ***************************************************************/

#include "client.h"
#include <time.h>

struct ClientInfo cltInfo;

/********************************************************
 *  Function:       int setupClientSocket(QWidget *parent);
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
 *      Responsible for socket creation. It creates the socket and
 *      attempts to connect to the server.
 *******************************************************/
int setupClientSocket(QWidget *parent)
{
    // create TCP socket and error check
    if((cltInfo.cltSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        QMessageBox::information(parent, "Error", "Failure to create socket");
        return -1;
    }
    else
    {
        printf("%s\n", "Client: Socket Created");
    }

    // set to user IPv4
    cltInfo.cltAddr.sin_family = AF_INET;

    // connect to server and error check
    if(connect(cltInfo.cltSock, (struct sockaddr *)&cltInfo.cltAddr, sizeof(cltInfo.cltAddr)) < 0)
    {
        QMessageBox::information(parent, "Error", "Failure to connect to server");
        return -1;
    }
    else
    {
        printf("%s\n", "Client: Connected to Server");
    }

    return 0;
}


/********************************************************
 *  Function:       bool validUsername(QString username, QWidget *parent)
 *
 *                      QString username  -  the username entered by the user
 *                      QWidget *parent   -  the current window in use
 *
 *  Return:         True if valid and False if invalid
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Checks for a valid username. Must be between 4 and 16 characters long
 *      and cannot contain any spaces. If the user did
 *      enter a username then their system name is used
 *      by default
 *******************************************************/
bool validUsername(QString username, QWidget *parent)
{
    // convert Qstring to a char*
    char tempUsername[INPUTBUFF];
    sprintf(tempUsername, username.toStdString().c_str());

    // check if nothing was entere (use default)
    if(username.length() == 0) // empty
    {
        // get system name
        gethostname(cltInfo.username, INPUTBUFF);
        return true;
    }

    // check if between 4 and 16
    if(username.length() > 16 || username.length() < 4)
    {
        QMessageBox::information(parent, "Error", "Error: Username must be between \n4 - 16 characters long");
        return false;
    }

    // check for spaces
    for(unsigned int i = 0; i < strlen(tempUsername); i++)
    {
        if(isspace(tempUsername[i]))
        {
            QMessageBox::information(parent, "Error", "Error: Username must not contain spaces");
            return false;
        }
    }

    // assign username
    strcpy(cltInfo.username, tempUsername);
    return true;
}


/********************************************************
 *  Function:       bool validClientPort(QString port, QWidget *parent)
 *
 *                      QString port  -  the port entered by user
 *                      QWidget *parent   -  the current window in use
 *
 *  Return:         True if valid and False if invalid
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Checks for a valid port. Must only contain digits and must
 *      not contains any spaces. If user entered nothing the port
 *      7000 is used by default
 *******************************************************/
bool validClientPort(QString port, QWidget *parent)
{
    char tempPort[INPUTBUFF];
    int _port;

    // convert QString to a char*
    sprintf(tempPort, port.toStdString().c_str());
    _port = atoi(tempPort);

    // check if nothing was entered (use default)
    if(port.length() == 0)
    {
        cltInfo.cltAddr.sin_port = htons(7000);
        return true;
    }

    // check for non digits and spaces
    for(unsigned int i = 0; i < strlen(tempPort); i++)
    {
        if(!isdigit(tempPort[i]))
        {
            QMessageBox::information(parent, "Error", "Error: Port must only contain digits");
            return false;
        }

        if(isspace(tempPort[i]))
        {
            QMessageBox::information(parent, "Error", "Error: Port must not contain spaces");
            return false;
        }
    }

    // assign port
    cltInfo.cltAddr.sin_port = htons(_port);
    return true;
}


/********************************************************
 *  Function:       bool validIP(QString ip, QWidget *parent)
 *
 *                      QString ip  -  the ip entered by user
 *                      QWidget *parent   -  the current window in use
 *
 *  Return:         True if valid and False if invalid
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Checks for a valid ip using gethostbyname
 *******************************************************/
bool validIP(QString ip, QWidget *parent)
{
    struct hostent *hp;

    // convert the QString to a char*
    char tempIP[INPUTBUFF];
    sprintf(tempIP, ip.toStdString().c_str());

    // check for a valid IP
    if((hp = gethostbyname(tempIP)) == NULL)
    {
        switch(h_errno)
        {
            case HOST_NOT_FOUND:
                QMessageBox::information(parent, "Error", "No such host found");
                return false;
            case TRY_AGAIN:
                QMessageBox::information(parent, "Error", "Host busy, try again later");
                return false;
            case NO_RECOVERY:
                QMessageBox::information(parent, "Error", "Host DNS error");
                return false;
            case NO_ADDRESS:
                QMessageBox::information(parent, "Error", "No such IP Address");
                return false;
            default:
                QMessageBox::information(parent, "Error", "Unknown error");
                return false;
        }
    }

    // assign IP
    cltInfo.cltAddr.sin_addr.s_addr = inet_addr(tempIP);
    inet_pton(AF_INET, tempIP, &(cltInfo.cltAddr.sin_addr));
    printf("%s\n", "Client: Valid host");
    return true;
}


/********************************************************
 *  Function:       void concatUsername(char *username)
 *
 *                      char *username  -  username display text
 *
 *  Return:         none
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *
 *  Desc:
 *      appends the username to the username display text
 *******************************************************/
void concatUsername(char *username)
{
    strcat(username, cltInfo.username);
}


/********************************************************
 *  Function:       void concatPort(char *port)
 *
 *                      char *port  -  port display text
 *
 *  Return:         none
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *
 *  Desc:
 *      appends the port to the port display text
 *******************************************************/
void concatPort(char *port)
{
    char tmpPort[INPUTBUFF];
    sprintf(tmpPort, "%hu",htons(cltInfo.cltAddr.sin_port));
    strcat(port, tmpPort);
}


/********************************************************
 *  Function:       void concatIP(char *ip)
 *
 *                      char *ip  -  ip display text
 *
 *  Return:         none
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *
 *  Desc:
 *      appends the ip to the ip display text
 *******************************************************/
void concatIP(char *ip)
{
    char *tmpIP= inet_ntoa(cltInfo.cltAddr.sin_addr);
    strcat(ip, tmpIP);
}


/********************************************************
 *  Function:       char * getUserMessage(ClientWindow *cw, char *IP, char *username)
 *                      ClientWindow *cw: ClientWindow pointer in order to access the UI
 *                      char *completeMsg: buffer that holds the complete message to send
 *                      char *IP: string containing the IP of the client sending the message
 *                      char *username: client username
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Will get the message entered by the user into the GUI.  Will then
 *      put a string with the IP and username appended to the front into the completeMsg buffer.
 *******************************************************/
void getUserMessage(ClientWindow *cw, char *completeMsg, char *IP, char *username)
{
    char msg[BUFLEN];

    cw->getUIMessage(msg);

    sprintf(completeMsg, "%s %s: %s", IP, username, msg);
}


/********************************************************
 *  Function:       void formatMessage(char *message, char *IP, char *username)
 *                      char *message: buffer that holds message to be formatted.
 *                      char *IP: string containing the IP of the client sending the message
 *                      char *username: client username
 *                      char *dest: where the formatted message should be written.
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      This will take the message passed into it and apply standard formatting rules.
 *      That is to say, It will prepend the message with the timestamp, username, and
 *      IP address of the sender. It will also colour code the username eventually.
 *******************************************************/
void formatMessage(const char *message, const char *IP, const char *username, char *dest)
{
    char timer[BUFLEN];
    time_t timestamp;
    struct tm * timeinfo;

    time(&timestamp);
    timeinfo = localtime(&timestamp);
    strftime(timer,BUFLEN,"<%b %d - %R>",timeinfo);
    sprintf(dest,"%s %s - %s: %s\n",timer, IP, username, message);
}
