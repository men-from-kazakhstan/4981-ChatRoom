// configdialog.h

#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>

#define DEFAULTPORT 8000

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    /* Qt created functions */
    explicit ConfigDialog(QWidget *parent = 0); // constructor
    ~ConfigDialog(); // destructor

private slots:
    /********************************************************
     *  Function:   on_cnfgOkButton_clicked()
     *
     *  Programmer: Alex Zielinski
     *
     *  Created: Mar 11 2017
     *
     *  Modified:
     *
     *  Desc:
     *      Event handler for when the OK button is
     *      clicked within the configuration dialog
     *      of the Client window. When clicked the
     *      username, port and IP data provided by
     *      user is validated. If something is invalid
     *      then the user is notifyed and the told to
     *      enter a valid value. Once all user entered
     *      data is valid then the data gets saved and
     *      the user is redirected to the Client window
     *******************************************************/
    void on_cnfgOkButton_clicked();

private:
    Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_H
