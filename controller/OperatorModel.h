#ifndef OPERATORMODEL_H
#define OPERATORMODEL_H

#include <QObject>
#include <QPair>
#include <QAbstractListModel>
#include "DatabaseManager.h"

class OperatorModel : public QAbstractListModel
{
    Q_OBJECT

    QList<QString> m_typeOperators;
    enum Roles
    {
        Operator_Name = Qt::UserRole + 1,
    };

public:
    explicit OperatorModel(QObject* parent = 0):
        QAbstractListModel(parent){initModel();}

    OperatorModel(const OperatorModel&) = default;
    OperatorModel& operator=(const OperatorModel&) = default;
    ~OperatorModel() = default;

    int rowCount(const QModelIndex &parent) const {Q_UNUSED(parent); return m_typeOperators.count();}
    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

 private:
    void initModel();
};

#endif // OPERATORMODEL_H
