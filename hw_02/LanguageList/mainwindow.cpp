#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    model->appendRow(new QStandardItem(QIcon("./Icons/c.png"), "Язык программирования C"));
    model->appendRow(new QStandardItem(QIcon("./Icons/cpp.png"), "Язык программирования C++"));
    model->appendRow(new QStandardItem(QIcon("./Icons/java.png"), "Язык программирования Java"));
    model->appendRow(new QStandardItem(QIcon("./Icons/python.png"), "Язык программирования Python"));
    model->appendRow(new QStandardItem(QIcon("./Icons/cs.png"), "Язык программирования C#"));
    model->appendRow(new QStandardItem(QIcon("./Icons/php.png"), "Язык программирования PHP"));
    model->appendRow(new QStandardItem(QIcon("./Icons/js.png"), "Язык программирования JavaScript"));
    //

    ui->listView->setModel(model);
    ui->listView->setDragEnabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->isChecked()) {
        ui->listView->setViewMode(QListView::IconMode);
    } else {
        ui->listView->setViewMode(QListView::ListMode);
    }
}


void MainWindow::on_pushButton_clicked()
{
    model->appendRow(new QStandardItem(QIcon("./Icons/def.png"),
                                      ui->lineEdit->text()));
}


void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(ui->listView->currentIndex().row());
}

