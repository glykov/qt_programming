#ifndef MYTABLEMODEL_H
#define MYTABLEMODEL_H

#include <QSqlTableModel>
#include <QObject>

class MyTableModel : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MyTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~MyTableModel();

    Q_INVOKABLE
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    Q_INVOKABLE
    virtual QHash<int, QByteArray> roleNames() const override;

    virtual void setTable(const QString &tableName) override;

private:
    QHash<int, QByteArray> roles;
    void generateRoleNames();
};

#endif // MYTABLEMODEL_H
