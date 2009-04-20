#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include <QtGui>

class MainWindow : public QMainWindow
{
    Q_OBJECT;

public:
    MainWindow(QWidget *parent=NULL);

private slots:
    void fileNew();
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void closeTab();
    void switchTab();
    void modified(bool changed);
    void testSlot();
    void loadFromBrowser(const QModelIndex &index);

private:
    bool load(const QString &fileName);
    

    QAction *actionSave;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;

    QSplitter *splitter;
    QDirModel *dirmodel;
    QListView *filebrowser;
    QTabWidget *tabArea;
    int tabinc;
    bool testbool;
};

#endif /* _MAINWINDOW_H */
