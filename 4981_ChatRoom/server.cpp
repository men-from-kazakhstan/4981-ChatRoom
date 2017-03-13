#include "server.h"

struct sockaddr_in serverAddr;
int srv_socket;

int setupServerSocket(QWidget* parent)
{
    //socklen_t size;
    int arg = 1;

    if((srv_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Socket created");
    }

    if(setsockopt(srv_socket, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Set socket options");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(srv_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        QMessageBox::information(parent, "Error", strerror(errno));
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Socket bind successful");
    }

    listen(srv_socket, 5);

    monitorConnections(parent);

    return 0;
}

int monitorConnections(QWidget* parent)
{
    struct sockaddr_in client_addr;
    int nready, maxfd, maxi, new_sd, client[FD_SETSIZE];
    socklen_t client_len;
    fd_set rset, allset;

    maxfd = srv_socket;
    maxi = -1;

    for(int i = 0; i < FD_SETSIZE; i++)
    {
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(srv_socket, &allset);
    while(true)
    {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);

        if(FD_ISSET(srv_socket, &rset))
        {
            client_len = sizeof(client_addr);
            if((new_sd = accept(srv_socket, (struct sockaddr *)&client_addr, &client_len)) < 0)
            {
                QMessageBox::information(parent, "Error",  strerror(errno));
                return -1;
            }
            else
            {
                QMessageBox::information(parent, "Info", "Client accepted");
            }
            printf(" Remote Address:  %s\n", inet_ntoa(client_addr.sin_addr));

            for (int i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = new_sd;	// save descriptor
                    break;
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
        }
    }
    return 0;
}


bool validServerPort(QString port, QWidget *parent)
{
     //QMessageBox::information(parent, "Error", "Error: Port must only contain digits");
    char tempPort[INPUTBUFF];
    int _port;
    sprintf(tempPort, port.toStdString().c_str());
    _port = atoi(tempPort);

    if(port.length() == 0)
    {
        serverAddr.sin_port = htons(7000);
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

    serverAddr.sin_port = htons(_port);
    return true;
}

