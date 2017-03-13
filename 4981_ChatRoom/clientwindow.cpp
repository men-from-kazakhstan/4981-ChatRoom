/****************************************************************
 * This is the Client window. This contains the actual chat
 * UI where a user can send messages to other clients connected
 * to the same server. It displays the connection information,
 * a Client list (client connected to server), chat display
 * area (to see messages from other clients), chat edit box (region
 * to enter a message to send to other clients). When the user
 * is redirected to this window they are prompted with a dialog
 * to enter configuration field (username, port, server IP to
 * connect to)
 ***************************************************************/

#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "configdialog.h"
#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QMessageBox>

/* constructor */
ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    char usernameDisplay[64] = "Username: ";
    char portDisplay[64] = "Port: ";
    char ipDisplay[64] = "Server: ";

    ui->setupUi(this);

    ConfigDialog *cd = new ConfigDialog();
    cd->exec();

    concatUsername(usernameDisplay);
    concatPort(portDisplay);
    concatIP(ipDisplay);
    ui->cltConfigDisplay->append(usernameDisplay);
    ui->cltConfigDisplay->append(portDisplay);
    ui->cltConfigDisplay->append(ipDisplay);

    setupClientSocket(this);
}

/* destructor */
ClientWindow::~ClientWindow()
{
    delete ui;
}

/* clients message send button event handler */
void ClientWindow::on_cltSendButton_clicked()
{

}
