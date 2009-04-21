#include "mainwindow.h"
#include "notebox.h"
//#include <QApplication>
//#include <QToolBar>
//#include <QTabWidget>
//#include <QMenuBar>
//#include <QMenu>
//#include <QTextEdit>
//#include <QClipboard>
//#include <QtGui> //includes all the above

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    tabinc = 0;
    //
    // file actions
    //
    //QToolBar *tb = addToolBar(tr("File Actions")); //draggable toolbar

    QMenu *menu = new QMenu(tr("File"), this);
    menuBar()->addMenu(menu);

    QAction *a;
    a = new QAction(tr("&New"), this);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    //tb->addAction(a);
    menu->addAction(a);

    //note: these shortcuts should be editable
    a = new QAction(tr("&Open"), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), SLOT(fileOpen()));
    menu->addAction(a);

    a = actionSave = new QAction(tr("&Save"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), SLOT(fileSave()));
    menu->addAction(a);

    a = new QAction(tr("Sa&ve As..."), this);
    connect(a, SIGNAL(triggered()), SLOT(fileSaveAs()));
    menu->addAction(a);

    a = new QAction(tr("Close Tab"), this);
    a->setShortcut(Qt::CTRL + Qt::Key_W);
    connect(a, SIGNAL(triggered()), SLOT(closeTab()));
    menu->addAction(a);
    menu->addSeparator();

    a = new QAction(tr("&Quit"), this);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(a, SIGNAL(triggered()), SLOT(close()));
    menu->addAction(a);

    //
    // edit actions
    //
    menu = new QMenu(tr("Edit"), this);
    menuBar()->addMenu(menu);

    a = actionUndo = new QAction(tr("&Undo"), this);
    a->setShortcut(QKeySequence::Undo);
    menu->addAction(a);
    
    a = actionRedo = new QAction(tr("&Redo"), this);
    a->setShortcut(QKeySequence::Redo);
    menu->addAction(a);
    menu->addSeparator();
    
    a = actionCut = new QAction(tr("Cut (&x)"), this);
    a->setShortcut(QKeySequence::Cut);
    menu->addAction(a);

    a = actionCopy = new QAction(tr("&Copy"), this);
    a->setShortcut(QKeySequence::Copy);
    menu->addAction(a);

    a = actionPaste = new QAction(tr("&Paste"), this);
    a->setShortcut(QKeySequence::Paste);
    menu->addAction(a);

    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());

    //setup filebrowser
    splitter = new QSplitter;
    //dirmodel = new QDirModel;
    filebrowser = new FileBrowser(splitter);
    //filebrowser->setModel(dirmodel);
    //filebrowser->setRootIndex(dirmodel->index(QDir::currentPath()+tr("\\..")));
    //filebrowser->setMovement(QListView::Snap);
    connect(filebrowser, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                SLOT(loadFromBrowser(QListWidgetItem*)));

    tabArea = new QTabWidget(splitter);
    tabArea->setMovable(true);
    splitter->setCollapsible(1, false);

    setCentralWidget(splitter);

    //Test slot!!! (write now it retracts/opens the filebrowser)
    testbool = false;
    a = new QAction(tr("&Klose"), this);
    a->setShortcut(Qt::CTRL + Qt::Key_K);
    connect(a, SIGNAL(triggered()), SLOT(testSlot()));
    menu->addAction(a);
    testSlot();

    //switch tab
    a = new QAction(tr("&Switch"), this);
    a->setShortcut(Qt::CTRL + Qt::Key_Tab);
    connect(a, SIGNAL(triggered()), SLOT(switchTab()));
    menu->addAction(a);

    NoteBox *box = new NoteBox(tabArea);

    tabArea->addTab(box,tr("*Untitled"));
    
    connect(box->textEdit()->document(),
            SIGNAL(modificationChanged(bool)), SLOT(modified(bool)));
    
    box->textEdit()->setFocus();
    //setCentralWidget(textArea); //place this in center

    //QTabBar *tb = new QTabBar(textArea);
    //tb->addTab(tr("tab"));

    setWindowTitle(tr("Editor"));

}

void MainWindow::loadFromBrowser(QListWidgetItem *item)
{
    QFileInfo fileInfo = QFileInfo((const QString&)item->data(5));
    if (fileInfo.isDir())
    {
        filebrowser->setDir(fileInfo.filePath());
    }
    else if (load(fileInfo.filePath()))
    {
    }
}

void MainWindow::testSlot()
{
    QList<int> list;
    if (testbool)
    {
        list.append(0);
        list.append(80);
        splitter->setSizes(list);
        testbool = false;
    }
    else
    {
        list.append(50);
        list.append(50);
        splitter->setSizes(list);
        testbool = true;
    }
}

void MainWindow::fileNew() //slot
{
    NoteBox *box = new NoteBox(tabArea);
    QTextEdit *edit = box->textEdit();
    tabArea->addTab(box,tr("*Untitled")+QString::number(++tabinc));
    connect(edit->document(),SIGNAL(modificationChanged(bool)), 
            SLOT(modified(bool)));
    tabArea->setCurrentWidget(box);
    edit->setFocus();
}
void MainWindow::fileOpen() //slot
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
            QString(), tr("Text Files (*.txt);;C++ Files (*.cpp *.h);;All Files (*)"));
    load(fileName);
}



bool MainWindow::fileSave() //slot
{
    //QFile file();
    //QTextStream ts(&file);
    
    return fileSaveAs();
}
bool MainWindow::fileSaveAs() //slot
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as..."),
            QString(), tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
        return false;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly))
        return false;
    QTextStream ts(&file);
    NoteBox *current = (NoteBox*)tabArea->currentWidget();
    ts << current->textEdit()->toPlainText();
    current->textEdit()->document()->setModified(false);

    tabArea->setTabText(tabArea->currentIndex(),QFileInfo(fileName).fileName());
    current->setHighlight(fileName.endsWith(".cpp") || fileName.endsWith(".h"));
    
    return true;
}

void MainWindow::closeTab()
{
    if (tabArea->count() > 1)
    {
        tabArea->removeTab(tabArea->currentIndex());
    }
    else
    {
        int tabIndex = tabArea->currentIndex();
        QString title = tabArea->tabText(tabIndex);
        NoteBox *current = (NoteBox*)tabArea->currentWidget();
        if(!title.startsWith("*Untitled") || title.endsWith(" +"))
        {
            current->textEdit()->clear();
            tabArea->setTabText(tabArea->currentIndex(),tr("*Untitled")+QString::number(++tabinc));
        }
    }
}

void MainWindow::switchTab()
{
    int nextIndex = tabArea->currentIndex()-1;
    if (nextIndex < 0)
        nextIndex = tabArea->count()-1;
    tabArea->setCurrentIndex(nextIndex);
    ((NoteBox*)tabArea->currentWidget())->textEdit()->setFocus();

}

bool MainWindow::load(const QString &fileName)
{
    NoteBox *current = (NoteBox*)tabArea->currentWidget();

    if (current == 0)
    {
        printf("loading null widget, fail\n");
        return false;
    }
    if (fileName.isNull())
        return false;
    
    if (!QFile::exists(fileName))
    {
        printf("fileName(%s) doesn't exist!\n",fileName.toAscii().constData());
        return false;
    }
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        printf("fileName(%s) failed to open\n",fileName.toAscii().constData());
        return false;
    }
    
    current->textEdit()->setPlainText(file.readAll());
    current->setHighlight(fileName.endsWith(".cpp") || fileName.endsWith(".h"));
    tabArea->setTabText(tabArea->currentIndex(),QFileInfo(fileName).fileName());
    return true;
}

void MainWindow::modified(bool changed)
{
    int index = tabArea->currentIndex();
    //setWindowTitle(tr("WTF"));
    if (changed)
    {
        tabArea->setTabText(index,tabArea->tabText(index)+tr(" +"));
    }
    else
    {
        QString title = tabArea->tabText(index);
        if (title.endsWith(" +"))
        {
            tabArea->setTabText(index,title.left(title.size()-2));
        }
    }
}




