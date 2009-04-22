#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) : QListWidget(parent)
{
    setDir(QDir::currentPath());
}

void FileBrowser::setDir(const QString &path)
{
    
    QDir dir = QDir(path);
    printf("set dir to (%s)\n",dir.path().toAscii().constData());
    dir.setSorting(QDir::DirsFirst | QDir::Name);
    QList<QFileInfo> list = dir.entryInfoList();
    clear();
    while (!list.isEmpty())
    {
        QFileInfo fileInfo = list.takeFirst();
        if (fileInfo.isDir())
        {
            if (fileInfo.fileName() == ".")
                continue;
        }
        else
        {
            if (fileInfo.suffix() != "txt" &&
                fileInfo.suffix() != "cpp" &&
                fileInfo.suffix() != "h")
            {
                continue;
            }
        }
        QIcon icon = dirModel.fileIcon(dirModel.index(fileInfo.filePath()));
        QListWidgetItem *item = new QListWidgetItem(icon,fileInfo.fileName(),this);
        item->setData(5,fileInfo.canonicalFilePath());
        addItem(item);
    }
}
