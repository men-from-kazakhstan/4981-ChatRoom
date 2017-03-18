/****************************************************************
 * This file contains all fucntions that deal with the client side
 * operations
 ***************************************************************/

#include "client.h"
#include <iostream>
#include <time.h>
#include <QFileDialog>
#include <QString>
#include <QTextStream>


using namespace std;

//client info struct
struct ClientInfo cltInfo;
//chat records
std::vector<std::string> chatHistory;
//client IP
char localip[BUFLEN];

/********************************************************
 *  Function:       int setupClientSocket(QWidget *parent);
 *
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:         return 1 on success and 0 on failure
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 13 2017
 *
 *  Modified:
 *                  Mar 16 2017 Pereparing local IP ~ Matt
 *                  Mar 17 2017 Refactoring code ~ Alex
 *
 *  Desc:
 *      Responsible for socket creation. Calls wrapper functions
 *      to create and connect the socket.
 *******************************************************/
int setupClientSocket(QWidget *parent)
{
    // create TCP socket and error check
    if (!createClientSocket(parent))
    {
        return 0;
    }
    else
    {
        printf("%s\n", "Client: Socket Created");
    }

    // connect to server and error check
    if (!connectSocket(parent))
    {
        return 0;
    }
    else
    {
        printf("%s\n", "Client: Connected to Server");
    }

    return 1;
}


/********************************************************
 *  Function:       int createClientSocket(QWidget *parent)
 *
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:         return 1 on success and 0 on failure
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 17 2017
 *
 *  Desc:
 *      Responsible for creating a socket
 *******************************************************/
int createClientSocket(QWidget *parent)
{
    // create TCP socket and error check
    if ((cltInfo.cltSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return 0;
    }

    return 1;
}


/********************************************************
 *  Function:       int createSocket(QWidget *parent)
 *
 *                      QWidget *parent  -  the current window in use
 *
 *  Return:         return 1 on success and 0 on failure
 *
 *  Programmer:     Alex Zielinski , Matt Goerwell
 *
 *  Created:        Mar 17 2017
 *
 *  Desc:
 *      Responsible for connecting socket to server. Also
 *      Stores the local IP address for later use.
 *******************************************************/
int connectSocket(QWidget *parent)
{
    // set to user IPv4
    cltInfo.cltAddr.sin_family = AF_INET;

    // connect to server and error check
    if (connect(cltInfo.cltSock, (struct sockaddr *)&cltInfo.cltAddr, sizeof(cltInfo.cltAddr)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return 0;
    }

    //setting up local ip;
    struct sockaddr_in local;
    socklen_t addressLength = sizeof(local);
    getsockname(cltInfo.cltSock, (struct sockaddr*)&local, &addressLength);
    sprintf(localip, "%s", inet_ntoa(local.sin_addr));

    return 1;
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
bool validUsername(char *username, QWidget *parent)
{
    // check if nothing was entered and display error if so
    if (strlen(username) == 0) // empty
    {
      QMessageBox::information(parent, "Error", "Error: You must enter a username");
      return false;
    }

    // check if between 4 and 16
    if (strlen(username) > 16 || strlen(username) < 4)
    {
        QMessageBox::information(parent, "Error", "Error: Username must be between \n4 - 16 characters long");
        return false;
    }

    // check for spaces
    for(unsigned int i = 0; i < strlen(username); i++)
    {
        if(isspace(username[i]))
        {
            QMessageBox::information(parent, "Error", "Error: Username must not contain spaces");
            return false;
        }
    }

    // assign username
    strcpy(cltInfo.username, username);
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
bool validClientPort(char *port, QWidget *parent)
{
    int tmpPort;

    // check if nothing was entered and display error if so
    if (strlen(port) == 0)
    {
        QMessageBox::information(parent, "Error", "Error: You must enter a port number");
        return false;
    }

    tmpPort = atoi(port);  // convert char* to int

    cltInfo.cltAddr.sin_port = htons(tmpPort);  // assign port
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
bool validIP(char *ip, QWidget *parent)
{
    struct hostent *hp;

    // check for a valid IP
    if ((hp = gethostbyname(ip)) == NULL)
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
    cltInfo.cltAddr.sin_addr.s_addr = inet_addr(ip);
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
 *  Function:       void processUserMessage(char *message, char *IP, ClientWindow *main)
 *                      char *message: buffer that holds message to be formatted.
 *                      ClientWindow *main: The UI for the client that sent the message.
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:       Mar 15 2017 - strings instead of char *
 *                  Mar 16 2017 - Including display and send method calls
 *
 *  Desc:
 *      This will take the message passed into it and apply standard formatting rules.
 *      That is to say, It will prepend the message with the timestamp, username, and
 *      IP address of the sender. It will also colour code the username eventually.
 *      Following this, it will call the methods required to store and send the
 *      message.
 *******************************************************/
void processUserMessage(const char *message, ClientWindow *main)
{
    char temp[BUFLEN];
    char timer[BUFLEN];

    time_t timestamp;
    struct tm * timeinfo;

    time(&timestamp);
    timeinfo = localtime(&timestamp);
    strftime(timer, BUFLEN, "<%b %d - %R>", timeinfo);
    sprintf(temp, "%s %s - %s: %s", timer, localip, cltInfo.username, message);
    std::string msg(temp);

    main->updateDisplay(msg.c_str());
    updateHistory(msg);
    sendToServer(msg.c_str(), BUFLEN);
}

/********************************************************
 *  Function:       void updateHistorystd::string message)
 *                      string message: the message we intend to store.
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 15 2017
 *
 *  Modified:
 *
 *  Desc:
 *  This is primarily a helper function for the saveSession function.
 *  It stores messages in our chat history.
 *******************************************************/
void updateHistory(std::string message)
{
    chatHistory.push_back(message);
}

/********************************************************
 *  Function:       receiveMessage(ClientWindow *main)
 *                      ClientWindow *main: a handle to the UI for message display
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 16 2017
 *
 *  Modified:
 *
 *  Desc:
 *      This is our primary read loop for the client. It will endlessy Poll the server for
 *      new data, extract it, then update both the display and the chat history.
 *******************************************************/
void receiveMessage(ClientWindow *main)
{
    char msg[BUFLEN];
    while (true)
    {
        getMsg(cltInfo.cltSock, msg, BUFLEN);
        string histMsg(msg);
        main->updateDisplay(histMsg.c_str());
        updateHistory(histMsg);
    }
}

/********************************************************
 *  Function:       void saveSession(Qwidget* main)
 *                      QWidget * main: a pointer to the main window.
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 15 2017
 *
 *  Modified:
 *
 *  Desc:
 *  This is our Session saving method. It prompts the user to select a location to save their file,
 *  then cretes/opens a file at that location. It then loops through the message history and writes
 *  the contents to the file.
 *******************************************************/
void saveSession(QWidget * main)
{
    QString filename = QFileDialog::getSaveFileName(main, "Save File", "/home", "Text Files (*.txt)");
    QFile handle(filename);
    if (handle.open(QIODevice::ReadWrite))
    {
        QTextStream out(&handle);
        for (auto& msg : chatHistory)
        {
            QString temp = QString::fromStdString(msg);
            out << temp << endl;
        }
        handle.close();
    }

}

/********************************************************
 *  Function:       void sendToServer(const char *msg, size_t msglen)
 *                      const char *msg: message to send
 *                      size_t msglen: length of message to send
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 15 2017
 *
 *  Modified:       Mar 16 2017 - Made the message const, since we shouldn't change it.
 *
 *  Desc:
 *      Simple function the ClientWindow class will call when it wants to send
 *      a message to the server.
 *******************************************************/
void sendToServer(const char *msg, size_t msglen)
{
    sendMsg(cltInfo.cltSock, msg, msglen);
}
