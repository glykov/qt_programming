#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QEvent>

#include "my_fileviewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_openButton_clicked();

    void on_saveButton_clicked();

    void on_refButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_switchLangButton_clicked();

    void on_styleButton_clicked();

    void on_printButton_clicked();

    void newFileAction();

    void copyText();
    void cutText();
    void pasteText();

private:
    Ui::MainWindow *ui;
    QString filter;
    QTranslator *translator;
    bool isRussian = true;
    bool isLightTheme = true;
    void changeEvent(QEvent *event) override;
    // menu items to be available for translation
    QMenu *fileMenu;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *printAction;
    QAction *exitAction;
    QMenu *editMenu;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QMenu *viewMenu;
    QAction *switchLangAction;
    QMenu *helpMenu;
    QAction *aboutAction;
};
#endif // MAINWINDOW_H
