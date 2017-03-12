// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* Qt created functions */
    explicit MainWindow(QWidget *parent = 0); // constructor
    ~MainWindow(); // destructor

private slots:
    /********************************************************
     *  Function:   on_clientButton_clicked()
     *
     *  Programmer: Alex Zielinski
     *
     *  Created: Mar 11 2017
     *
     *  Modified:
     *
     *  Desc:
     *      Event handler for when the Client button is
     *      clicked. It hides the current window and
     *      displays the Client window (redirect user to
     *      Client window)
     *******************************************************/
    void on_clientButton_clicked();

    /********************************************************
     *  Function:   on_serverButton_clicked()
     *
     *  Programmer: Alex Zielinski
     *
     *  Created: Mar 11 2017
     *
     *  Modified:
     *
     *  Desc:
     *      Event handler for when the Server button is
     *      clicked. It hides the current window and
     *      displays the Server window (redirect user to
     *      server window)
     *******************************************************/
    void on_serverButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
