#include "organizer.h"
#include <sql_interface.h>
#include <QSqlRecord>
#include <QDebug>


#define RELEASE(p) if (p) {delete p; p = NULL;}

Organizer::Organizer(QObject* parent) : QObject(parent)
{
    try {
        sqlInterface = new SQLInterface(dbPath);
    } catch (const std::exception &ex) {
            qDebug() << ex.what();

    };
    m_modelPtr = sqlInterface->getTableModel();
    if (getLength()>0){
        currentIndex = 0;
        currentTask = sqlInterface->getRow(currentIndex).second;
    }
    emit modelChanged();
}

Organizer::~Organizer()
{
    RELEASE(sqlInterface);
}


void Organizer::nextTask()
{
    if (currentIndex < getLength()-1){
        currentIndex++;
        currentTask = sqlInterface->getRow(currentIndex).second;
        emit indexChanged();
    }
}

void Organizer::prevTask()
{
    if (currentIndex > 0){
        currentIndex--;
        currentTask = sqlInterface->getRow(currentIndex).second;
        emit indexChanged();
    }
}

int Organizer::getIndex() const
{
    return currentIndex;
}

int Organizer::getLength() const
{
    return sqlInterface->rowsCount();
}

QString Organizer::getCurrentTaskTitle() const
{
    return currentTask.getTitle();
}

QString Organizer::getCurrentTaskDeadline() const
{
    return currentTask.getDeadline();
}

int Organizer::getCurrentTaskPriority() const
{
    return currentTask.getPriority();
}

MyTableModel* Organizer::getTableModel() const
{
    return m_modelPtr;
}

void Organizer::addNewTask(QString title, QString deadline, int priority)
{
    sqlInterface->addRow(title,deadline,priority);
    currentTask.setTitle(title);
    currentTask.setDeadline(deadline);
    currentTask.setPriority(priority);
    currentIndex = getLength()-1;
    emit lengthChanged();
    emit indexChanged();
    emit modelChanged();
}
