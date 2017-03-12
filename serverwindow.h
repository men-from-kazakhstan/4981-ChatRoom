// serverwindow.h

#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>

namespace Ui {
class ServerWindow;
}

class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* Qt created functions */
    explicit ServerWindow(QWidget *parent = 0); // constructor
    ~ServerWindow(); // destructor

private slots:
    /********************************************************
     *  Function:   on_srvStartStopButton_clicked()
     *
     *  Programmer: Alex Zielinski
     *
     *  Created: Mar 11 2017
     *
     *  Modified:
     *
     *  Desc:
     *      Event handler for when the Client start button
     *      is clicked on the server (as to start the
     *      server). Once clicked a TCP socket will be created
     *      using the port value the user entered (default is
     *      used if nothing was entered). If the port is invalid
     *      then the user is notifyed and the server does not
     *      start (until a valid port is entered). Once the
     *      socket has been created and is listenening then
     *      the status label will be updated.
     *******************************************************/
    void on_srvStartStopButton_clicked();

private:
    Ui::ServerWindow *ui;
};

#endif // SERVERWINDOW_H
