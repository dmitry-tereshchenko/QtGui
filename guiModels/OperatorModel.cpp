#include "OperatorModel.h"

QVariant OperatorModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() < m_typeOperators.size())
    {
        switch (role)
        {
        case Roles::Operator_Name:
            return m_typeOperators.at(index.row());
        default:
            break;
        }
    }
    return QVariant();
}

QHash<int, QByteArray> OperatorModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Roles::Operator_Name, "operatorName");
    return roles;
}

void OperatorModel::initModel()
{
    DatabaseManager::getInstanse()->getOperators(m_typeOperators);
}
