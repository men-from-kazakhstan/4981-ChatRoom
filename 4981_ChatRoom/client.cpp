#include "client.h"

struct ClientInfo cltInfo;

int setupClientSocket(QWidget *parent)
{
    //int _port = atoi(port);
    if((cltInfo.cltSock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        QMessageBox::information(parent, "Error", "Failure to create socket");
        return -1;
    }
    else
    {
        //QMessageBox::information(parent, "Info", "Socket created");
        printf("%s\n", "Client Socket Created");
    }

    cltInfo.cltAddr.sin_family = AF_INET;

    if(connect(cltInfo.cltSock, (struct sockaddr *)&cltInfo.cltAddr, sizeof(cltInfo.cltAddr)) < 0)
    {
        QMessageBox::information(parent, "Error", "Failure to connect to server");
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Connected to server");
        //printf("%s\n", "Client Connected to Server");
    }

    return 0;
}


bool validUsername(QString username, QWidget *parent)
{
    char tempUsername[INPUTBUFF];

    sprintf(tempUsername, username.toStdString().c_str());

    if(username.length() == 0) // empty
    {

        gethostname(cltInfo.username, INPUTBUFF);
        return true;
    }

    if(username.length() > 16 || username.length() < 4)
    {
        QMessageBox::information(parent, "Error", "Error: Username must be between \n4 - 16 characters long");
        return false;
    }

    for(unsigned int i = 0; i < strlen(tempUsername); i++)
    {
        if(isspace(tempUsername[i]))
        {
            QMessageBox::information(parent, "Error", "Error: Username must not contain spaces");
            return false;
        }
    }

    strcpy(cltInfo.username, tempUsername);
    return true;
}


bool validClientPort(QString port, QWidget *parent)
{
    char tempPort[INPUTBUFF];
    int _port;
    sprintf(tempPort, port.toStdString().c_str());
    _port = atoi(tempPort);

    if(port.length() == 0)
    {
        //QMessageBox::information(parent, "Error", "Error: Must enter port");
        cltInfo.cltAddr.sin_port = htons(7000);
        return true;
    }

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

    cltInfo.cltAddr.sin_port = htons(_port);
    //inet_pton(AF_INET, tempPort, &(cltInfo.cltAddr.sin_port));
    return true;
}


bool validIP(QString ip, QWidget *parent)
{
    struct hostent *hp;
    char tempIP[INPUTBUFF];

    sprintf(tempIP, ip.toStdString().c_str());

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

    cltInfo.cltAddr.sin_addr.s_addr = inet_addr(tempIP);
    inet_pton(AF_INET, tempIP, &(cltInfo.cltAddr.sin_addr));
    //QMessageBox::information(parent, "Info", "Valid Host");
    printf("%s\n", "Valid host");
    return true;
}

void concatUsername(char *username)
{
    strcat(username, cltInfo.username);
}


void concatPort(char *port)
{
    char tmpPort[INPUTBUFF];
    sprintf(tmpPort, "%hu",htons(cltInfo.cltAddr.sin_port));
    strcat(port, tmpPort);
}


void concatIP(char *ip)
{
    char *tmpIP= inet_ntoa(cltInfo.cltAddr.sin_addr);
    strcat(ip, tmpIP);
}
