#include "server.h"

struct sockaddr_in serverAddr, newCltAddr;
int srv_socket;
char srvPort[INPUTBUFF];

int setupServerSocket(QWidget* parent, int *sock, sockaddr_in srvAddr, sockaddr_in newAddr, char port[INPUTBUFF])
{
    socklen_t size;
    int arg = 1;
    int _port = atoi(port);

    if((*sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Socket created");
    }

    if(setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Set socket options");
    }

    srvAddr.sin_family = AF_INET;
    srvAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    srvAddr.sin_port = htons(_port);

    if(bind(*sock, (struct sockaddr *)&srvAddr, sizeof(srvAddr)) < 0)
    {
        QMessageBox::information(parent, "Error", strerror(errno));
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Socket bind successful");
    }

    listen(*sock, 5);

    size = sizeof(newAddr);
    if(accept(*sock, (struct sockaddr *)&newAddr, &size) < 0)
    {
        QMessageBox::information(parent, "Error",  strerror(errno));
        return -1;
    }
    else
    {
        QMessageBox::information(parent, "Info", "Client accepted");
    }

    return 0;
}
