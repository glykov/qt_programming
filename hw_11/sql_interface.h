#ifndef SQL_INTERFACE_H
#define SQL_INTERFACE_H

#include <QString>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QPair>

class SQLInterface
{
public:
    SQLInterface(QString);
    ~SQLInterface();

    bool addRow(QString, QString, int);
    QPair<bool,class Task> getRow(int);

    int rowsCount();

    class MyTableModel *getTableModel() const;

private:
    class MyTableModel* tableModel;
    QSqlDatabase db;

    void init(QString);
    bool create_table(QString);
};

#endif // SQL_INTERFACE_H
