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
    // set status of server
    ui->srvStatusLabel->setText("Status: OFF");

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
        if (setupServerSocket(this) == 1)
        {
             ui->srvStatusLabel->setText("Status: ON");
        }
    }
}

/********************************************************
 *  Function:       void ServerWindow::updateClients(const char *client)
 *                      const char *client: Client IP address
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Adds a connected client to the servers client list
 *******************************************************/
void ServerWindow::updateClients(const char *client)
{
    char newClient[CLIENT_SIZE];
    sprintf(newClient, "%s", client);
    ui->srvClientList->addItem(newClient);
}


/********************************************************
 *  Function:       void ServerWindow::removeClient(const char *client)
 *                      const char *client: Client IP address
 *
 *  Programmer:     Alex Zielinski
 *
 *  Created:        Mar 20 2017
 *
 *  Modified:
 *
 *  Desc:
 *      removes a client from the servers client list
 *******************************************************/
void ServerWindow::removeClient(const char *client)
{
    QListWidgetItem *item;
    char delClient[CLIENT_SIZE]; // hold client string to delete
    char itemText[CLIENT_SIZE]; // hold string content of list item
    sprintf(delClient, "%s", client); // copy char param to buffer

    // iterate through the client list
    for (int row = 0; row < ui->srvClientList->count(); row++)
    {
        item = ui->srvClientList->item(row); // get current item
        sprintf(itemText, item->text().toStdString().c_str()); // copys the items string content

        // if list item is matches the client string the delete
        if (strcmp(itemText, delClient) == 0)
        {  // remove current client row from list
           ui->srvClientList->takeItem(row);
        }
    }
}
