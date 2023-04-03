#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addHtmlButton_clicked()
{
    ui->firstTextEdit->setHtml("<h1><font color='red'>Hello</font></h1>");
}


void MainWindow::on_clearButton_clicked()
{
    ui->firstTextEdit->clear();
    ui->secondTextEdit->clear();
}


void MainWindow::on_addButton_clicked()
{
    ui->secondTextEdit->append(ui->firstTextEdit->toPlainText());
}


void MainWindow::on_moveButton_clicked()
{
    ui->firstTextEdit->setText(ui->secondTextEdit->toPlainText());
    ui->secondTextEdit->clear();
}

