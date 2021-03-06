#ifndef EDITABLESQLMODEL_H
#define EDITABLESQLMODEL_H

#include <QSqlQueryModel>

class editablesqlmodel : public QSqlQueryModel
{
    Q_OBJECT

public:
    editablesqlmodel(QObject *parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    bool setFirstName(int personId, const QString &firstName);
    bool setLastName(int personId, const QString &lastName);
    void refresh();
};

#endif // EDITABLESQLMODEL_H
