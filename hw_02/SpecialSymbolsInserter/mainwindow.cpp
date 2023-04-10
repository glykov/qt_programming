#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parser = new ParseSymbol();
}

MainWindow::~MainWindow()
{
    delete parser;
    delete ui;
}


void MainWindow::on_textEdit_textChanged()
{
    QString inStr = ui->textEdit->toPlainText();
    QString outStr = parser->parse(inStr);
    //ui->textEdit->clear();
    ui->textEdit->setPlainText(outStr);
}

