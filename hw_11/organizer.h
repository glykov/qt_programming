#ifndef ORGANIZER_H
#define ORGANIZER_H

#include "task.h"
#include <QObject>
#include <QSqlTableModel>
#include "mytablemodel.h"

#define dbPath "tasks.db"

class Organizer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int index READ getIndex NOTIFY indexChanged);
    Q_PROPERTY(int totalTasks READ getLength NOTIFY lengthChanged);
    Q_PROPERTY(QString currentTaskTitle READ getCurrentTaskTitle);
    Q_PROPERTY(QString currentTaskDeadline READ getCurrentTaskDeadline);
    Q_PROPERTY(int currentTaskPriority READ getCurrentTaskPriority);
    Q_PROPERTY(MyTableModel* model MEMBER m_modelPtr READ getTableModel NOTIFY modelChanged);
public:
    Organizer(QObject* parent = nullptr);
    ~Organizer();

    Q_INVOKABLE
    void nextTask();
    Q_INVOKABLE
    void prevTask();
    Q_INVOKABLE
    void addNewTask(QString, QString, int);


    int getIndex() const;
    int getLength() const;

    QString getCurrentTaskTitle() const;
    QString getCurrentTaskDeadline() const;
    int getCurrentTaskPriority() const;
    MyTableModel* getTableModel() const;

private:
    int currentIndex = -1;
    Task currentTask;
    class SQLInterface* sqlInterface;
    MyTableModel* m_modelPtr;

signals:
    void lengthChanged();
    void indexChanged();
    void fileOpenError();
    void modelChanged();
};

#endif // ORGANIZER_H
