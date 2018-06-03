#include "mysqlquerymodel.h"
#include <QtSql>
#include <QColor>
#include <QDebug>

MySqlQueryModel::MySqlQueryModel(QObject *parent):
    QSqlQueryModel(parent)
{

}

//更改数据显示样式
QVariant MySqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if (role == Qt::TextColorRole && index.column() == 0)
        return QVariant::fromValue(QColor(Qt::red));
    return value;
}

Qt::ItemFlags MySqlQueryModel::flags(const QModelIndex &index) const //返回表格是否可更改的标志
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 1) //第二个字段可更改
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool MySqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int /* role */)
//添加数据
{
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int id = data(primaryKeyIndex).toInt(); //获取id号
    clear();

    bool ok;
    if (index.column() == 1)
    {
        ok = setName(id, value.toString());
    }
    refresh();
    qDebug() << ok;
    return ok;
}

void MySqlQueryModel::refresh() //更新显示
{
    setQuery("select * from student");
    setHeaderData(0, Qt::Horizontal, tr("id"));
    setHeaderData(1, Qt::Horizontal, tr("name"));
}

//添加name字段的值
bool MySqlQueryModel::setName(int studentId, const QString &Name)
{
    QSqlQuery query;
    query.prepare("update student set name = ? where id = ?");
    query.addBindValue(Name);
    query.addBindValue(studentId);
    if (!query.exec())
    {
        qDebug() << query.lastError().text() << endl;
    }
    return query.exec();
}
