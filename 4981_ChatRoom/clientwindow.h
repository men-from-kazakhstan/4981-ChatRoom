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

    void getUIMessage(char *pmsg);
    void updateDisplay(const char *msg);

private slots:
    void on_cltSendButton_clicked();
    void on_cltSaveButton_clicked();

private:
    Ui::ClientWindow *ui;
};

#endif // CLIENTWINDOW_H
