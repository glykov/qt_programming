#ifndef FILEVIEWER_H
#define FILEVIEWER_H

#include <QApplication>
#include <QWidget>
#include <QStandardItemModel>
#include <QGridLayout>
#include <QTreeView>
#include <QPushButton>
#include <QComboBox>

Q_PROPERTY(QStandardItemModel *model READ getCurrentModel WRITE setNewModel)

class FileViewer : public QWidget
{
    Q_OBJECT

public:
    explicit FileViewer(QWidget *parent = nullptr);
    void createTree();
    QStandardItemModel *getCurrentModel() const {
        return model;
    }
    void setNewModel(QStandardItemModel *newModel);
    void rebuildModel(QString str);

private slots:
    void changeDrive(int index);
    void goMainPath();

private:
    QStandardItemModel *model;
    QString currentPath;
    QGridLayout *layout;
    QTreeView *treeView;
    QPushButton *mainPath;
    QComboBox *driveSelectionBox;
};

#endif // FILEVIEWER_H
