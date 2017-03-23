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
#include "client.h"
using namespace std;

//string ConfigDialog::colour = "\e[0;34m";
string ConfigDialog::colour = "black";

/********************************************************
 *  Constructor: ConfigDialog
 *
 *  Programmer:  Alex Zielinski, Robert Arendac
 *
 *  Created:     Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Sets the UI of the config dialog and sets default
 *      setting values
 *******************************************************/
ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{

    char tmpUsername[INPUTBUFF];
    ui->setupUi(this); // display configuration dialog

    configMap();

    // set the port edit text to only take ints
    ui->cnfgPortEdit->setValidator(new QIntValidator);
    // set port to default value
    ui->cnfgPortEdit->setText("7000");

    // set username to default value
    getlogin_r(tmpUsername, INPUTBUFF); // get system name
    ui->cnfgUsernameEdit->setText(tmpUsername);
}

/********************************************************
 *  Destructor: ConfigDialog
 *
 *  Programmer:  default qt code
 *
 *  Created:     Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Free's config dialog ui
 *******************************************************/
ConfigDialog::~ConfigDialog()
{
    delete ui;
}

/********************************************************
 *  Function: void ConfigDialog::on_cnfgOkButton_clicked()
 *
 *  Programmer:  Alex Zielinski
 *
 *  Created:     Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      On click function for config dialog. Goes through
 *      each setting options and checks if user input is
 *      valid
 *******************************************************/
void ConfigDialog::on_cnfgOkButton_clicked()
{
    int validFlag = 1;

    // convert user input from QString to char*
    char cUsername[INPUTBUFF];
    char cPort[INPUTBUFF];
    char cIP[INPUTBUFF];
    sprintf(cUsername, ui->cnfgUsernameEdit->text().toStdString().c_str());
    sprintf(cPort, ui->cnfgPortEdit->text().toStdString().c_str());
    sprintf(cIP, ui->cnfgServerIPEdit->text().toStdString().c_str());

    // check for valid username
    if (!validUsername(cUsername, this))
    {
        ui->cnfgUsernameEdit->clear(); // clear the username edit text
        validFlag = 0;
    }

    // check for valid port
    if (!validClientPort(cPort, this))
    {
        ui->cnfgPortEdit->clear(); // clear the port edit text
        validFlag = 0;
    }

    // check for valid IP
    if (!validIP(cIP, this))
    {
        ui->cnfgServerIPEdit->clear(); // clear the ip edit text
        validFlag = 0;
    }

    // check if any of the field were invalid
    if (validFlag)
    {
        setColour();
        this->close(); // close the current window
    }
}

/********************************************************
 *  Function:       void ConfigDialog::configMap()
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 19 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Sets up a map containing all the colours in the GUI
 *******************************************************/
void ConfigDialog::configMap()
{
    QList<QRadioButton *> allButtons = ui->groupBox->findChildren<QRadioButton *>();

    for (int i = 0; i < allButtons.size(); i++)
    {
        colourCodes.insert(pair<int, string>(i, allButtons[i]->text().toStdString()));
    }

}

/********************************************************
 *  Function:       string ConfigDialog::getColour()
 *
 *  Return:         String of the colour name
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 19 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Gets the user-selected colour
 *******************************************************/
string ConfigDialog::getColour() {
    return colour;
}

/********************************************************
 *  Function:       void ConfigDialog::setColour()
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 19 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Goes through all radio buttons and sets the colour
 *      to whichever one is selected
 *******************************************************/
void ConfigDialog::setColour()
{
    QButtonGroup group;
    QList<QRadioButton *> allButtons = ui->groupBox->findChildren<QRadioButton *>();

    for (int i = 0; i < allButtons.size(); i++)
    {
        group.addButton(allButtons[i], i);
    }

    colour = colourCodes.find(group.checkedId())->second;
}
