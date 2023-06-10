#include "sql_interface.h"
#include "task.h"
#include "mytablemodel.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QPair>
#include "errno.h"

#define RELEASE(p) if (p) {delete p; p = NULL;}
#define TABLE_NAME "tasks"

SQLInterface::SQLInterface(QString dbpath)
{
    init(dbpath);
    if (create_table(TABLE_NAME)){
        tableModel = new MyTableModel(nullptr,db);
        tableModel->setTable(TABLE_NAME);
        tableModel->select();
        tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    };
}

SQLInterface::~SQLInterface()
{
    RELEASE(tableModel);
}

bool SQLInterface::addRow(QString title, QString deadline, int priority)
{
    db.transaction();

    QSqlRecord newTask = tableModel->record();
    newTask.remove(newTask.indexOf("id"));
    newTask.setValue("title",title);
    newTask.setValue("deadline",deadline);
    newTask.setValue("priority",priority);

    if (tableModel->insertRecord(-1,newTask)) {
        tableModel->submitAll();
        db.commit();
        return true;
    } else {
        db.rollback();
        return false;
    }
}

QPair<bool, Task> SQLInterface::getRow(int index)
{
    if (index>=rowsCount() || index<0){
        return qMakePair(false,Task{"","",0});
    }
    QSqlRecord task = tableModel->record(index);
    Task result{task.value("title").toString(), task.value("deadline").toString(), task.value("priority").toInt()};
    return qMakePair(true,result);
}


int SQLInterface::rowsCount()
{
    return tableModel->rowCount();
}

MyTableModel *SQLInterface::getTableModel() const
{
    return tableModel;
}


void SQLInterface::init(QString dbpath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbpath);
    if (!db.open()){
        throw std::runtime_error("Error openning database!");
    }
}

bool SQLInterface::create_table(QString tableName)
{
    QSqlQuery query;
    QString s("CREATE TABLE IF NOT EXISTS "+tableName+" ( "
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "title TEXT NOT NULL,"
            "deadline TEXT NOT NULL,"
            "priority INTEGER NOT NULL DEFAULT 0);");
    return query.exec(s);

}
