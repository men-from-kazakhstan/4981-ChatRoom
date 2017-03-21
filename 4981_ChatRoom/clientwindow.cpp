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
#include <thread>

/* constructor */
ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    // text to display config info
    char usernameDisplay[64] = "Username: ";
    char portDisplay[64] = "Port: ";
    char ipDisplay[64] = "Server: ";

    ui->setupUi(this);

    ConfigDialog *cd = new ConfigDialog();
    cd->exec();

    // setup to the clients TCP socket
    if(setupClientSocket(this) < 1)
    {
        ConfigDialog *cd = new ConfigDialog();
        cd->exec();
    }

    // concatinate user entered data to display text
    concatUsername(usernameDisplay);
    concatPort(portDisplay);
    concatIP(ipDisplay);

    // display config data
    ui->cltConfigDisplay->append(usernameDisplay);
    ui->cltConfigDisplay->append(portDisplay);
    ui->cltConfigDisplay->append(ipDisplay);

    //If we can connect properly, start our receiving thread ~Matt
    std::thread reading(receiveMessage, this);
    reading.detach();
}

/* destructor */
ClientWindow::~ClientWindow()
{
    delete ui;
}

/********************************************************
 *  Function:   on_cltSendButton_clicked()
 *
 *  Programmer: Alex Zielinski
 *
 *  Created: Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Event handler for when the send button is
 *      clicked on the clients side, notifying
 *      that the user wants to send a message to
 *      the chat
 *******************************************************/
void ClientWindow::on_cltSendButton_clicked()
{
    char message[BUFLEN];
    getUIMessage(message);
    processUserMessage(message, this);
}

/********************************************************
 *  Function:   on_cltSaveButton_clicked()
 *
 *  Programmer: Matt Goerwell
 *
 *  Created: Mar 15 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Event handler for when the save button is
 *      clicked on the clients side, notifying
 *      that the user wants to save the chat to a file.
 *******************************************************/
void ClientWindow::on_cltSaveButton_clicked()
{
    saveSession(this);
}

/********************************************************
 *  Function:       updateDisplay(const char *msg)
 *                      const char *msg: string containing the message to be displayed.
 *
 *  Programmer:     Matt Goerwell
 *
 *  Created:        Mar 15 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Takes the message passed in and writes it to the chat display.
 *******************************************************/
void ClientWindow::updateDisplay(const char *msg)
{
    ui->cltChatDisplay->append(msg);
}

/********************************************************
 *  Function:       getUIMessage(char *pmsg)
 *                      char *pmsg: string to hold the message from GUI
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Gets the message from the UI and inserts it into pmsg
 *******************************************************/
void ClientWindow::getUIMessage(char *pmsg)
{
    sprintf(pmsg, ui->cltChatEdit->toPlainText().toStdString().c_str());
}
