/****************************************************************
 * This is the main window of the program as it is the first
 * window of the program. This window prompts the user if they
 * want to be a client or a server via two buttons labeled
 * respectably in the window. Clicking on the Client button
 * will redirect the user to the client window. Clicking on
 * the server window will redirect the user to the server
 * window
 ***************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serverwindow.h"
#include "clientwindow.h"

/********************************************************
 *  Constructor: MainWindow
 *
 *  Programmer:  Default qt code
 *
 *  Created:     Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Sets up ui
 *******************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this); // display MainWindow
}

/********************************************************
 *  Destructor: MainWindow
 *
 *  Programmer:  Default qt code
 *
 *  Created:     Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Free's ui
 *******************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/********************************************************
 *  Function: void MainWindow::on_clientButton_clicked()
 *
 *  Programmer:  Alex Zielinski
 *
 *  Created:     Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Onclick function for when the user clicks on the
 *      clien button. Closes the current window and
 *      opens the client window
 *******************************************************/
void MainWindow::on_clientButton_clicked()
{
    this->hide(); // hide the current window
    // create and show the client window
    ClientWindow *cw = new ClientWindow();
    cw->show();
}

/********************************************************
 *  Function: void MainWindow::on_serverButton_clicked()
 *
 *  Programmer:  Alex Zielinski
 *
 *  Created:     Mar 11 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Onclick function for when the user clicks on the
 *      server button. Closes the current window and
 *      opens the server window
 *******************************************************/
void MainWindow::on_serverButton_clicked()
{
    this->hide(); // hide the current window
    // create and show server window
    ServerWindow *sw = new ServerWindow();
    sw->show();
}
