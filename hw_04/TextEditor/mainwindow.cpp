#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    filter = trUtf8("Текстовый файл (*.txt)");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть", QDir::current().path(), filter);

    if (fileName.length() > 0) {
        int index = fileName.indexOf(".txt");

        if (index != -1 && fileName.length() - 4 == index) {
            QFile fin(fileName);
            if (fin.open(QFile::ReadOnly | QFile::ExistingOnly)) {
                QTextStream stream(&fin);
                stream.setCodec("UTF-8");
                ui->plainTextEdit->setPlainText(stream.readAll());
                fin.close();
            }
        }
    }
}


void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить", QDir::current().path(), filter);

    if (fileName.length() > 0) {
        QString ext = QString(&(fileName.data()[fileName.length() - 4]));
        if (ext == ".txt") {
            QFile fout(fileName);
            if (fout.open(QFile::WriteOnly | QFile::NewOnly)) {
                QTextStream stream(&fout);
                stream.setCodec("UTF-8");
                stream << ui->plainTextEdit->toPlainText();
                fout.close();
            }
        }
    }
}


void MainWindow::on_refButton_clicked()
{
    QFile helpFile(":/help/help.txt");
    if (helpFile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&helpFile);
        stream.setCodec("UTF-8");
        QString str = stream.readAll();
        QMessageBox::information(this, "Справка", str);
    }
}

/*
 * 1. Добавить в текстовый редактор режим «Открыть только для чтения»,
 * блокирующий любые правки для документа.
*/
void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->isChecked()) {
        ui->plainTextEdit->setReadOnly(true);
    } else {
        ui->plainTextEdit->setReadOnly(false);
    }
}

/*
 * 2. Перевести текстовый редактор на английский язык (названия кнопок из предыдущих заданий).
 * Добавить возможность динамически переключать языки во время работы приложения.
*/
void MainWindow::on_switchLangButton_clicked()
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    if (isRussian) {
        translator->load(":/tr/QtLanguage_en.qm");
        isRussian = false;
    } else {
        translator->load("ru");
        isRussian = true;
    }
    QApplication::installTranslator(translator);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        setWindowTitle(tr("Текстовый редактор"));
        ui->openButton->setText(tr("Открыть"));
        ui->saveButton->setText(tr("Сохранить"));
        ui->refButton->setText(tr("Справка"));
        ui->switchLangButton->setText(tr("Переключить язык"));
        ui->checkBox->setText(tr("Только для чтения"));
    } else {
        QMainWindow::changeEvent(event);
    }
}

/*
 * 3. Добавить в текстовый редактор возможность пользоваться сочетаниями клавиш:
 * ctrl+o - открыть новый документ,
 * ctrl+s - сохранить как,
 * ctrl+n - создать новый документ,
 * ctrl+q - выход из программы.
*/

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        switch(event->key()) {
        case Qt::Key_O:
            on_openButton_clicked();
            break;
        case Qt::Key_S:
            on_saveButton_clicked();
            break;
        case Qt::Key_Q:
            QApplication::quit();
            break;
        case Qt::Key_N:
            on_saveButton_clicked();
            ui->plainTextEdit->clear();
            break;
        default:
            QWidget::keyReleaseEvent(event);
        }
    }
}
