#include <QDir>
#include "fileviewer.h"

FileViewer::FileViewer(QWidget *parent) : QWidget(parent), model(nullptr)
{
    layout = new QGridLayout(this);
    this->setLayout(layout);

    treeView = new QTreeView(this);
    layout->addWidget(treeView, 1, 0, 10, 10);
    setMinimumSize(500, 600);

    if(QSysInfo::productType() == "windows") {
        driveSelectionBox = new QComboBox(this);
        QFileInfoList list = QDir::drives();
        QFileInfoList::const_iterator listDrives = list.begin();

        int amount = list.count();
        for (int i = 0; i < amount; ++i) {
            driveSelectionBox->addItem(listDrives->path());
            ++listDrives;
        }

        if (amount > 0) {
            rebuildModel(list.at(0).path());
        }

        layout->addWidget(driveSelectionBox, 0, 0, 1, 2);

        connect(driveSelectionBox, SIGNAL(activated(int)), this, SLOT(changeDrive(int)));
    } else {
        mainPath = new QPushButton(this);
        mainPath->setText("/");
        layout->addWidget(mainPath, 0, 0, 1, 2);
        connect(mainPath, SIGNAL(clicked()), this, SLOT(goMainPath()));
        rebuildModel("/");
    }
}

void FileViewer::setNewModel(QStandardItemModel *newModel)
{
    treeView->setModel(newModel);
    model = newModel;
}

void FileViewer::rebuildModel(QString str)
{
    currentPath = str;
    QStandardItemModel *model = new QStandardItemModel(this);
    QList<QStandardItem*> items;
    items.append(new QStandardItem(
                     QIcon(QApplication::style()->standardIcon(QStyle::SP_DriveHDIcon)),
                     str));
    model->appendRow(items);

    QDir dir(str);
    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Dirs);
    QStringList list = dir.entryList();
    int amount = list.count();
    QList<QStandardItem*> folders;
    for (int i = 0; i < amount; ++i) {
        QStandardItem *f = new QStandardItem(
                    QIcon(QApplication::style()->standardIcon(QStyle::SP_DirIcon)),
                    list.at(i));
        folders.append(f);
    }
    items.at(0)->appendRows(folders);

    dir.setFilter(QDir::Hidden | QDir::NoSymLinks | QDir::Files);
    list = dir.entryList();
    amount = list.count();
    QList<QStandardItem*> files;
    for (int i = 0; i < amount; ++i) {
        QStandardItem *f = new QStandardItem(
                    QIcon(QApplication::style()->standardIcon(QStyle::SP_FileIcon)),
                    list.at(i));
        files.append(f);
    }

    items.at(0)->appendRows(files);

    setNewModel(model);
}

void FileViewer::changeDrive(int index)
{
    QFileInfoList list = QDir::drives();
    rebuildModel(list.at(index).path());
}

void FileViewer::goMainPath()
{
    rebuildModel("/");
}
