#include "mytablemodel.h"
#include <QSqlRecord>

MyTableModel::MyTableModel(QObject *parent, QSqlDatabase db) :  QSqlTableModel(parent,db)
{

}

MyTableModel::~MyTableModel()
{

}

QHash<int, QByteArray> MyTableModel::roleNames() const
{
    return roles;
}

void MyTableModel::setTable(const QString &tableName)
{
    QSqlTableModel::setTable(tableName);
    generateRoleNames();
}

void MyTableModel::generateRoleNames()
{
    roles.clear();
    roles[Qt::DisplayRole] = "display";
}

QVariant MyTableModel::data(const QModelIndex &index, int role) const
{
    QVariant value;

    if (index.isValid()) {
        if (role < Qt::UserRole) {
            value = QSqlQueryModel::data(index, role);
        } else {
            int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(index.row(), columnIdx);
            value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
    }
    return value;
}
