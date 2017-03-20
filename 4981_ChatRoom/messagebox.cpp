/****************************************************************
 * This is a custom QTextEdit class that will emit a signal when
 * the enter key is typed instead of going to a newline
 ***************************************************************/

#include "messagebox.h"
#include "clientwindow.h"
#include "client.h"

MessageBox::MessageBox(QWidget *parent) : QTextEdit(parent) {
    setPlaceholderText("Type Your Message Here!");
}

/********************************************************
 *  Function:       void MessageBox::keyPressEvent(QKeyEvent *e)
 *                      QKeyEvent *e:  Key event the function is responding to
 *
 *  Return:         Return 1 on success and 0 on failure
 *
 *  Programmer:     Robert
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
        default:
            QTextEdit::keyPressEvent(e);
            break;
    }
}
