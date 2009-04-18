
#include "notebox.h"
#define CUR_LINE

NumberBar::NumberBar(QWidget *parent) : QWidget(parent), edit(0)
{
    // Start with room for 2 digits
    setFixedWidth(fontMetrics().width(QString("00"))+2);
}

void NumberBar::setTextEdit(QTextEdit *edit)
{
    this->edit = edit;
    //connect to repaint event
    connect(edit->document()->documentLayout(), SIGNAL(update(const QRectF &)), this, SLOT(update()));
    connect(edit->document(), SIGNAL(blockCountChanged(int)), this, SLOT(setBarWidth(int)));
    connect(edit->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(update()));
}

void NumberBar::setBarWidth(int newBlockCount)
{
    int digits;
    newBlockCount/=10;
    for (digits=2; newBlockCount/=10; digits++);
    setFixedWidth(fontMetrics().width(QString("0"))*digits+2);
    update();
}

void NumberBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QAbstractTextDocumentLayout *layout = edit->document()->documentLayout();
    QTextBlock block = edit->document()->begin();
    int vscrollValue = edit->verticalScrollBar()->value();
    for (int i=1; block.isValid(); i++, block=block.next())
    {
        const QRectF rect = layout->blockBoundingRect(block);
        if (block.isVisible()) {
            painter.drawText(-1, qRound(rect.top())-vscrollValue+1,
                    width(), fontMetrics().height(), Qt::AlignRight, QString::number(i));
        }
        else if (rect.top() > vscrollValue)
        {
            break;
        }
    }
}




NoteBox::NoteBox(QWidget *parent) : QFrame(parent)
{
    //setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    //setLineWidth(2);

    // Setup the main view
    view = new QTextEdit(this);
    view->setFontFamily("Courier");
    //view->setLineWrapMode(QTextEdit::NoWrap);
    //view->setFrameStyle(QFrame::NoFrame);
    //view->installEventFilter(this); //inherited from QObject

    highlighter = new Highlighter(view->document());

    // Setup the line number pane
    numbers = new NumberBar( this );
    numbers->setTextEdit(view);

    box = new QHBoxLayout(this);
    box->setSpacing(0);
    box->setMargin(0);
    box->addWidget(numbers);
    box->addWidget(view);

    connect(view, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    highlightCurrentLine();
}


void NoteBox::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> selects;
    QTextEdit::ExtraSelection select;
    
    QColor lineColor = QColor(Qt::blue).lighter(180);

    select.format.setBackground(lineColor);
    select.format.setProperty(QTextFormat::FullWidthSelection, true);
    select.cursor = view->textCursor();
    select.cursor.clearSelection();
    selects.append(select);

    view->setExtraSelections(selects);

}

void NoteBox::setHighlight(bool toggle)
{
    highlighter->toggle = toggle;
    highlighter->rehighlight();
}
