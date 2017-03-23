/****************************************************************
 * This is the main entry point of the program
 ***************************************************************/

#include "mainwindow.h"
#include <QApplication>

/********************************************************
 *  Function: int main(int argc, char *argv[])
 *                int argc: Number of command line arguments
 *                char *argv[]: Array of command line arguments
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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
