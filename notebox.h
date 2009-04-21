#ifndef _NOTEBOX_H
#define _NOTEBOX_H

//#include <QFrame>
//#include <QPixmap>
//#include <QTextCursor>

//class QTextEdit;
//class QHBoxLayout;

#include <QtGui>
#include "highlighter.h"

/**
 * @internal Used to display the numbers.
 */
class NumberBar : public QWidget
{
    Q_OBJECT;

public:
    NumberBar(QWidget *parent);

    void setTextEdit(QTextEdit *edit);
    //void paintEvent(QPaintEvent *ev);

private slots:
    void setBarWidth(int);

private:
    void paintEvent(QPaintEvent *);
    QTextEdit *edit;
};

/**
 * Displays a QTextEdit with line numbers.
 */
class NoteBox : public QFrame
{
    Q_OBJECT;

public:

    NoteBox(QWidget *parent=NULL);
    QTextEdit *textEdit() { return view; }
    void setHighlight(bool toggle);
    QString path;

protected slots:
    void highlightCurrentLine();

private:
    QTextEdit *view;
    Highlighter *highlighter;
    NumberBar *numbers;
    QHBoxLayout *box;
};


#endif // _NOTEBOX_H

