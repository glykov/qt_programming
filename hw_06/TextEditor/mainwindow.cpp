#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>
#include <QPrinter>
#include <QPrintDialog>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    filter = trUtf8("Text file (*.txt)");

    /*
     * 1. Добавить меню в текстовый редактор.
    */
    // add file menu and its items
    fileMenu = menuBar()->addMenu(tr("&File"));
    newAction = fileMenu->addAction(tr("&New"));
    newAction->setShortcut(tr("Ctrl+N"));
    openAction = fileMenu->addAction(tr("&Open"));
    openAction->setShortcut(tr("Ctrl+O"));
    saveAction = fileMenu->addAction(tr("&Save"));
    saveAction->setShortcut(tr("Ctrl+S"));
    fileMenu->addSeparator();
    printAction = fileMenu->addAction(tr("Print"));
    printAction->setShortcut(tr("Ctrl+P"));
    fileMenu->addSeparator();
    exitAction = fileMenu->addAction(tr("E&xit"));
    exitAction->setShortcut(tr("Ctrl+Q"));
    /* connect to slots */
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFileAction()));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(on_openButton_clicked()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(on_saveButton_clicked()));
    connect(printAction, SIGNAL(triggered(bool)), this, SLOT(on_printButton_clicked()));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    // add edit menu and its items
    editMenu = menuBar()->addMenu(tr("&Edit"));
    copyAction = editMenu->addAction(tr("Copy"));
    copyAction->setShortcut(tr("Ctrl+C"));
    cutAction = editMenu->addAction(tr("Cut"));
    cutAction->setShortcut(tr("Ctrl+X"));
    pasteAction = editMenu->addAction(tr("Paste"));
    pasteAction->setShortcut(tr("Ctrl+V"));
    connect(copyAction, SIGNAL(triggered(bool)), this, SLOT(copyText()));
    connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(cutText()));
    connect(pasteAction, SIGNAL(triggered(bool)), this, SLOT(pasteText()));
    // add view menu and its items
    viewMenu = menuBar()->addMenu(tr("&View"));
    switchLangAction = viewMenu->addAction(tr("Change &Language"));
    connect(switchLangAction, SIGNAL(triggered(bool)),
            this, SLOT(on_switchLangButton_clicked()));
    // add help menu and its items
    helpMenu = menuBar()->addMenu(tr("&Help"));
    aboutAction = helpMenu->addAction(tr("A&bout"));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(on_refButton_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open", QDir::current().path(), filter);

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
    QString fileName = QFileDialog::getSaveFileName(this, "Save", QDir::current().path(), filter);

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
        QMessageBox::information(this, "Help", str);
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->isChecked()) {
        ui->plainTextEdit->setReadOnly(true);
    } else {
        ui->plainTextEdit->setReadOnly(false);
    }
}

void MainWindow::on_styleButton_clicked()
{
    if (isLightTheme) {
        QFile style(":/styles/darkTheme.qss");
        style.open(QFile::ReadOnly);
        qApp->setStyleSheet(style.readAll());
        style.close();
        isLightTheme = false;
    } else {
        QFile style(":/styles/aquaTheme.qss");
        style.open(QFile::ReadOnly);
        qApp->setStyleSheet(style.readAll());
        style.close();
        isLightTheme = true;
    }
}

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
        setWindowTitle(tr("Text Editor"));
        ui->openButton->setText(tr("Open"));
        ui->saveButton->setText(tr("Save"));
        ui->refButton->setText(tr("Help"));
        ui->styleButton->setText(tr("Change Style"));
        ui->switchLangButton->setText(tr("Change Language"));
        ui->checkBox->setText(tr("Read Only"));
        ui->printButton->setText(tr("Print"));
        fileMenu->setTitle(tr("&File"));
        newAction->setText(tr("&New"));
        openAction->setText(tr("&Open"));
        saveAction->setText(tr("&Save"));
        printAction->setText(tr("Print"));
        exitAction->setText(tr("E&xit"));
        editMenu->setTitle(tr("&Edit"));
        copyAction->setText(tr("Copy"));
        cutAction->setText(tr("Cut"));
        pasteAction->setText(tr("Paste"));
        viewMenu->setTitle(tr("&View"));
        switchLangAction->setText(tr("Change &Language"));
        helpMenu->setTitle(tr("&Help"));
        aboutAction->setText(tr("A&bout"));
    } else {
        QMainWindow::changeEvent(event);
    }
}

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
            newFileAction();
            break;
        case Qt::Key_P:
            on_printButton_clicked();
            break;
        case Qt::Key_C:
            copyText();
            break;
        case Qt::Key_V:
            pasteText();
            break;
        case Qt::Key_X:
            cutText();
            break;
        default:
            QWidget::keyReleaseEvent(event);
        }
    }
}

/*
 * 2. Добавить в текстовый редактор кнопку для вывода на печать
*/
void MainWindow::on_printButton_clicked()
{
    QPrinter printer;
    QPrintDialog printDialog(&printer, this);
    printDialog.setWindowTitle(tr("Print"));
    if (printDialog.exec() != QDialog::Accepted) {
        return;
    }
    ui->plainTextEdit->print(&printer);
}

void MainWindow::newFileAction()
{
    ui->plainTextEdit->clear();
}

void MainWindow::copyText()
{
    QString str = ui->plainTextEdit->textCursor().selectedText();
    qApp->clipboard()->setText(str);
}

void MainWindow::cutText()
{
    QString str = ui->plainTextEdit->textCursor().selectedText();
    qApp->clipboard()->setText(str);
    ui->plainTextEdit->textCursor().removeSelectedText();
}

void MainWindow::pasteText()
{
    QString str = qApp->clipboard()->text();
    ui->plainTextEdit->textCursor().insertText(str);
}

