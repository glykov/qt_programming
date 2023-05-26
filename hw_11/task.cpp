#include "task.h"
#include <QDataStream>

Task::Task(QString title_, QString deadline_, int priority_)
{
    setTitle(title_);
    setPriority(priority_);
    setDeadline(deadline_);
}

Task::Task()
{

}

QString Task::getTitle() const
{
    return title;
}

void Task::setTitle(QString value)
{
    title = value;
}

QString Task::getDeadline() const
{
    return deadline.toString("dd.MM.yyyy");
}

void Task::setDeadline(QString value)
{
    deadline = QDate::fromString(value,"dd.MM.yyyy");
}

int Task::getPriority() const
{
    return priority;
}

void Task::setPriority(int value)
{
    if (value < 0) priority = 0;
    else if (value >10) priority = 10;
    else priority = value;
}

void Task::writeToStream(QDataStream &stream)
{
    auto bytes = title.toUtf8();
    int len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);

    bytes = getDeadline().toUtf8();
    len = bytes.length();
    stream.writeRawData((char*)&len, sizeof len);
    stream.writeRawData(bytes.data(), len);

//    bytes.setNum(priority);
//    stream.writeRawData(bytes, len);
    len = priority;
    stream.writeRawData((char*)&len,sizeof len);
}

void Task::readFromStream(QDataStream &stream)
{
    int len = 0;
    QByteArray b;

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    setTitle(QString::fromUtf8(b));

    stream.readRawData((char*)&len, sizeof len);
    b.resize(len);
    stream.readRawData(b.data(), len);
    setDeadline(QString::fromUtf8(b));

    stream.readRawData((char*)&len, sizeof len);
    setPriority(len);
}
