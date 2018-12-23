#include "DocumentProtocol.h"
#include <controller/DatabaseManager.h>

int DocumentProtocol::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QVariant DocumentProtocol::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (!index.isValid() || m_data.count() == 0)
        value = QVariant();

    if(index.row() < 0 || index.row() >= m_data.count())
        value = QVariant();

    if (role == RoleName::Header_Id)
        value = m_data.at(index.row()).id;

    if(role == RoleName::Header_Information)
        value = m_data.at(index.row()).information;

    if(role == Header_Command)
        value = m_data.at(index.row()).command;

    return value;
}

void DocumentProtocol::resetData()
{
    if(m_data.size()){
        m_data.clear();
        refresh();
    }
}

QHash<int, QByteArray> DocumentProtocol::roleNames() const
{
    return m_roleNames;
}

void DocumentProtocol::refresh()
{
    beginResetModel();
    endResetModel();
}

void DocumentProtocol::initModel()
{
    m_roleNames[RoleName::Header_Id] = "id";
    m_roleNames[RoleName::Header_Information] = "information";
    m_roleNames[RoleName::Header_Command] = "command";

    resetData();

    QList<Documents::DocProtocolInfo> info = DatabaseManager::getInstanse()->getDocProtocol();
    if(info.size()){
        for(auto it = info.constBegin(); it != info.end(); ++it)
        {
            DocInfo totalDoc;
            totalDoc.id = (*it).id;
            totalDoc.information = (*it).information;
            totalDoc.command = (*it).command;

            m_data.push_back(totalDoc);
        }
    }
    refresh();
}
