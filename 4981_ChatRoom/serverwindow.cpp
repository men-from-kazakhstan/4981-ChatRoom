/****************************************************************
 * This window is for the server. All it contains in regards to
 * UI is a field to enter the port to use, a start server button,
 * and a list of conencted clients to the server. The server
 * is responsible for received messages from different clients
 * and relay that message to all other clients.
 ***************************************************************/

#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "server.h"
#include "client.h"

/* constructor */
ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
}

/* destructor */
ServerWindow::~ServerWindow()
{
    delete ui;
}

/* server start button event handler*/
void ServerWindow::on_srvStartStopButton_clicked()
{
    // check for valid port
    if(validPort(ui->srvPortEdit->text(), this))
    {
        // if valid copy the port to a char array
        sprintf(srvPort, ui->srvPortEdit->text().toStdString().c_str());
        setupServerSocket(this, &srv_socket, serverAddr, newCltAddr, srvPort);
    }
    else
    {
        ui->srvPortEdit->clear(); // clear the username edit text
    }
}
