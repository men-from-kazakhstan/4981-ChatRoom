/****************************************************************
 * This is a custom QTextEdit class that will emit a signal when
 * the enter key is typed instead of going to a newline
 ***************************************************************/

#include "messagebox.h"
#include "clientwindow.h"
#include "client.h"

/********************************************************
 *  Constructor:       void MessageBox::keyPressEvent(QKeyEvent *e)
 *                      QKeyEvent *e:  Key event the function is responding to
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 20 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Overrides the QTextEdit method to emit a single when
 *      the "return" or "enter" key is pressed instead of going
 *      to a newline
 *******************************************************/
MessageBox::MessageBox(QWidget *parent) : QTextEdit(parent)
{
    setPlaceholderText("Type Your Message Here!");
}

/********************************************************
 *  Function:       void MessageBox::keyPressEvent(QKeyEvent *e)
 *                      QKeyEvent *e:  Key event the function is responding to
 *
 *  Programmer:     Robert Arendac
 *
 *  Created:        Mar 20 2017
 *
 *  Modified:
 *
 *  Desc:
 *      Overrides the QTextEdit method to emit a single when
 *      the "return" or "enter" key is pressed instead of going
 *      to a newline
 *******************************************************/
void MessageBox::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            emit sendUserMessage();
            return;
        case Qt::Key_Backspace:
            QTextEdit::keyPressEvent(e);
        default:
            if (this->toPlainText().length() < BUFLEN - 75) {   //Extra padding allowed for formatting
                QTextEdit::keyPressEvent(e);
                break;
            }
    }
}
