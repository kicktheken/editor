#ifndef _FILEBROWSER_H
#define _FILEBROWSER_H

#include <QtGui>

class FileBrowser : public QFrame
{
    Q_OBJECT;
public:
    FileBrowser(QWidget *parent=NULL);
    void setDir(const QString &path);
    QListWidget *view;
private slots:
    void resolvePath();
private:
    QDir curDir;
    QDirModel dirModel;
    QLineEdit *pathEdit;
    QVBoxLayout *layout;
};

#endif /* _FILEBROWSER_H */
