#ifndef CUSTOMSQLMODEL_H
#define CUSTOMSQLMODEL_H

#include <QSqlQueryModel>

class customsqlmodel : public QSqlQueryModel
{
    Q_OBJECT

public:
    customsqlmodel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &item, int role) const override;
};

#endif // CUSTOMSQLMODEL_H
