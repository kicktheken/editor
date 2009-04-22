#include "filebrowser.h"

FileBrowser::FileBrowser(QWidget *parent) : QFrame(parent)
{
    pathEdit = new QLineEdit(this);
    view = new QListWidget(this);
    layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(" File Browser");
    
    layout->setSpacing(5);
    layout->setContentsMargins(5,5,0,5);
    layout->addWidget(label);
    layout->addWidget(pathEdit);
    layout->addWidget(view);
    
    setDir(QDir::currentPath());
    
    connect(pathEdit, SIGNAL(editingFinished()), SLOT(resolvePath()));
}

// @pre dir is valid path
void FileBrowser::setDir(const QString &path)
{
    curDir = QDir(path);
    //printf("set dir to (%s)\n",curDir.path().toAscii().constData());
    pathEdit->setText(curDir.path());
    curDir.setSorting(QDir::DirsFirst | QDir::Name);
    QList<QFileInfo> list = curDir.entryInfoList();
    view->clear();
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
        QListWidgetItem *item = new QListWidgetItem(icon,fileInfo.fileName(),view);
        item->setData(5,fileInfo.canonicalFilePath());
        view->addItem(item);
    }
}

void FileBrowser::resolvePath()
{
    QDir dir = QDir(pathEdit->text());
    if (dir.exists())
    {
        setDir(dir.path());
    }
    else
    {
        pathEdit->setText(curDir.path());
    }
}
