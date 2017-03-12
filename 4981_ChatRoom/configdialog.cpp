/****************************************************************
 * This is the configurations dialog for the client window. When
 * the user is redirected to the Client window they are
 * immediatly prompted with the configurations dialog which prompts
 * them to enter a user name, and port to user and the server IP
 * they want to connect to. All field are checked for validity.
 * This dialog shall also be available to the user through the
 * menu bar
 ***************************************************************/
#include "configdialog.h"
#include "ui_configdialog.h"

/* constructor */
ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this); // display configuration dialog
}

/* destructor */
ConfigDialog::~ConfigDialog()
{
    delete ui;
}

/* config dialog OK button event handler */
void ConfigDialog::on_cnfgOkButton_clicked()
{
    this->close(); // close the current window
}
