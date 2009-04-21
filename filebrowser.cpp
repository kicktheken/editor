#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) : QListWidget(parent)
{
    QDirModel dirmodel;
    QList<QFileInfo> list = QDir::current().entryInfoList();
    while (!list.isEmpty())
    {
        QFileInfo fileinfo = list.takeFirst();
        QIcon icon = dirmodel.iconProvider()->icon(fileinfo);
        QListWidgetItem *item = new QListWidgetItem(icon,fileinfo.fileName(),this);
        addItem(item);
    }
}
