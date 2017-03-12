// clientwindow.h

#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* Qt created functions */
    explicit ClientWindow(QWidget *parent = 0); // constructor
    ~ClientWindow(); // destructor

private slots:
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
    void on_cltSendButton_clicked();

private:
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
