#include <QtMath>
#include <QRegExpValidator>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QRegExp regExp("[-]{0,1}[0-9]+");
    QValidator *v = new QRegExpValidator(regExp, this);
    ui->aLineEdit->setValidator(v);
    ui->bLineEdit->setValidator(v);
    ui->cLineEdit->setValidator(v);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_clearButton_clicked()
{
    ui->aLineEdit->clear();
    ui->bLineEdit->clear();
    ui->cLineEdit->clear();
}


void MainWindow::on_exitButton_clicked()
{
    this->close();
}


void MainWindow::on_calculateButton_clicked()
{
    double x1, x2;
    QString result = "";
    int a = ui->aLineEdit->text().toInt();
    int b = ui->bLineEdit->text().toInt();
    int c = ui->cLineEdit->text().toInt();

    if (a != 0) {
        double discrim = b * b - 4 * a * c;
        if (discrim > 0) {
            x1 = (-b + qSqrt(discrim)) / (2 * a);
            x2 = (-b - qSqrt(discrim)) / (2 * a);
            result += "x1 = " + QString::number(x1) + ", x2 = " + QString::number(x2);
        } else if (discrim < 0){
            result += "Нет корней";
        } else {
            x1 = -b / (2 * a);
            result += "x = " + QString::number(x1);
        }
    } else {
        x1 = -c / b;
        result += "x = " + QString::number(x1);
    }

    ui->resultLabel->setText(result);
}

