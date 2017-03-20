#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QWidget>
#include <QTextEdit>
#include <QKeyEvent>


class MessageBox : public QTextEdit
{
    Q_OBJECT

public:
    MessageBox(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent *e);

signals:
    void sendUserMessage();

};

#endif // MESSAGEBOX_H
