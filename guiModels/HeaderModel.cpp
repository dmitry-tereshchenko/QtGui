#include "HeaderModel.h"

QVariant HeaderModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() < m_typeHeader.size())
    {
        switch (role)
        {
        case Roles::Header_Image:
            return m_typeHeader.at(index.row()).first;
            break;
        case Roles::Header_Name:
            return m_typeHeader.at(index.row()).second;
            break;
        default:
            break;
        }
    }
    return QVariant();
}

QHash<int, QByteArray> HeaderModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Roles::Header_Image, "headerImage");
    roles.insert(Roles::Header_Name, "headerName");
    return roles;
}

void HeaderModel::initModel()
{
    m_map.insert(QObject::tr("Menu"), Name::MENU);
    m_map.insert(QObject::tr("Home"), Name::HOME);
    m_map.insert(QObject::tr("Documents"), Name::DOCUMENTS);
    m_map.insert(QObject::tr("Control"), Name::CONTROL);
    m_map.insert(QObject::tr("Settings"), Name::SETTINGS);
    m_map.insert(QObject::tr("Copyright"), Name::LOGOUT);

    m_typeHeader.append(qMakePair(QString("menu.png"), m_map.key(Name::MENU)));
    m_typeHeader.append(qMakePair(QString("home.png"), m_map.key(Name::HOME)));
    m_typeHeader.append(qMakePair(QString("analysis.png"), m_map.key(Name::DOCUMENTS)));
    m_typeHeader.append(qMakePair(QString("control.png"), m_map.key(Name::CONTROL)));
    m_typeHeader.append(qMakePair(QString("settings.png"), m_map.key(Name::SETTINGS)));
    m_typeHeader.append(qMakePair(QString("copyright.png"), m_map.key(Name::LOGOUT)));
}
