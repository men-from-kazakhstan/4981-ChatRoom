#include "client.h"

struct sockaddr_in clientAddr;
int clt_socket;
char cltUsername[INPUTBUFF];
char cltPort[INPUTBUFF];
char cltIP[INPUTBUFF];

int setupClientSocket(QWidget *parent, int *sock, sockaddr_in cltAddr, char port[INPUTBUFF], char ip[INPUTBUFF])
{
    int _port = atoi(port);

    if((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        QMessageBox::information(parent, "Error", "Failure to create socket");
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Socket created");
    }

    cltAddr.sin_family = AF_INET;
    cltAddr.sin_addr.s_addr = inet_addr(ip);
    cltAddr.sin_port = htons(_port);

    if(connect(*sock, (struct sockaddr *)&cltAddr, sizeof(cltAddr)) < 0)
    {
        QMessageBox::information(parent, "Error", "Failure to connect to server");
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Connected to server");
    }

    return 0;
}


bool validUsername(QString username, QWidget *parent)
{
    char temp[INPUTBUFF];

    sprintf(temp, username.toStdString().c_str());

    if(username.length() > 16 || username.length() < 4)
    {
        QMessageBox::information(parent, "Error", "Error: Username must be between \n4 - 16 characters long");
        return false;
    }

    for(unsigned int i = 0; i < strlen(temp); i++)
    {
        if(isspace(temp[i]))
        {
            QMessageBox::information(parent, "Error", "Error: Username must not contain spaces");
            return false;
        }
    }
    return true;
}


bool validPort(QString port, QWidget *parent)
{
    char temp[INPUTBUFF];

    sprintf(temp, port.toStdString().c_str());

    if(strlen(temp) == 0)
    {
        QMessageBox::information(parent, "Error", "Error: Must enter port");
        return false;
    }

    for(unsigned int i = 0; i < strlen(temp); i++)
    {
        if(!isdigit(temp[i]))
        {
            QMessageBox::information(parent, "Error", "Error: Port must only contain digits");
            return false;
        }

        if(isspace(temp[i]))
        {
            QMessageBox::information(parent, "Error", "Error: Port must not contain spaces");
            return false;
        }
    }

    return true;
}


bool validIP(QString ip, QWidget *parent)
{
    struct hostent *hp;
    char temp[INPUTBUFF];

    sprintf(temp, ip.toStdString().c_str());

    if((hp = gethostbyname(temp)) == NULL)
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

    QMessageBox::information(parent, "Info", "Valid Host");

    return true;
}
