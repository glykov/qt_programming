#include <QtMath>
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


void MainWindow::on_exitButton_clicked()
{
    this->close();
}


void MainWindow::on_clearButton_clicked()
{
    ui->aSideLineEdit->clear();
    ui->bSideLineEdit->clear();
    ui->angleLineEdit->clear();
    ui->resultLabel->setText("");
}


void MainWindow::on_calculateButton_clicked()
{
    QString result = "";
    double a = ui->aSideLineEdit->text().toDouble();
    double b = ui->bSideLineEdit->text().toDouble();
    double angle = ui->angleLineEdit->text().toDouble();
    if (ui->degreeRadioButton->isChecked()) {
        angle = qDegreesToRadians(angle);
    }
    double c = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos(angle));

    result += "Длина стороны c = " + QString::number(c);
    ui->resultLabel->setText(result);
}

