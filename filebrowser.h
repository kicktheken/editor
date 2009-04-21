#ifndef _FILEBROWSER_H
#define _FILEBROWSER_H

#include <QtGui>

class FileBrowser : public QListWidget
{
    Q_OBJECT;
public:
    FileBrowser(QWidget *parent=NULL);
private:
    QString filter;
};

#endif /* _FILEBROWSER_H */