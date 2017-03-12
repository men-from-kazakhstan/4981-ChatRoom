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

/* constructor */
ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    ConfigDialog *cd = new ConfigDialog();
    cd->exec();
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

void ClientWindow::getUIMessage(char *pmsg) {
    sprintf(pmsg, ui->cltChatEdit->toPlainText().toStdString().c_str());
}
