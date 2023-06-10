#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QDate>

class Task
{
public:
    Task(QString, QString, int);
    Task();

    QString getTitle() const;
    void setTitle(QString value);

    QString getDeadline() const;
    void setDeadline(QString value);

    int getPriority() const;
    void setPriority(int value);

    void writeToStream(QDataStream& stream);
    void readFromStream(QDataStream& stream);

private:
    QString title;
    QDate deadline;
    int priority;
};

#endif // TASK_H
