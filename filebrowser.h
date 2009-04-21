#ifndef _FILEBROWSER_H
#define _FILEBROWSER_H

#include <QtGui>

class FileBrowser : public QListWidget
{
    Q_OBJECT;
public:
    FileBrowser(QWidget *parent=NULL);
    void setDir(const QString &path);
private:
    QDirModel dirModel;
};

#endif /* _FILEBROWSER_H */
