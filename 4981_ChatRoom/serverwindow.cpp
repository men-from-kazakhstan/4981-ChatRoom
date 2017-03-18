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

/* constructor */
ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);

    // set the port edit text to only take ints
    ui->srvPortEdit->setValidator(new QIntValidator);
    // set port to default value
    ui->srvPortEdit->setText("7000");

}

/* destructor */
ServerWindow::~ServerWindow()
{
    delete ui;
}

/* server start button event handler */
void ServerWindow::on_srvStartStopButton_clicked()
{
    // convert user input from QString to char*
    char cPort[INPUTBUFF];
    sprintf(cPort, ui->srvPortEdit->text().toStdString().c_str());

    // check for valid port
    if (!validServerPort(cPort, this))
    {

        ui->srvPortEdit->clear(); // clear the username edit text
    }
    else
    {
        setupServerSocket(this);
    }
}

/* Add a new client to the server window */
void ServerWindow::updateClients(int client)
{
    char newClient[CLIENT_SIZE];
    sprintf(newClient, "%d", client);
    ui->srvClientList->addItem(newClient);
}
