#include "SessionReport.h"
#include <controller/DatabaseManager.h>

int SessionReport::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_data.count();
}

QVariant SessionReport::data(const QModelIndex &index, int role) const
{
    QVariant value;
    if (!index.isValid() || m_data.count() == 0)
        value = QVariant();

    if(index.row() < 0 || index.row() >= m_data.count())
        value = QVariant();

    if (role == RoleName::Header_Id)
        value = m_data.at(index.row()).id;

    if(role == RoleName::Header_Name)
        value = m_data.at(index.row()).name;

    if(role == Header_Time_Start)
        value = m_data.at(index.row()).beginTime;

    if(role == Header_Time_End)
        value = m_data.at(index.row()).endTime;

    return value;
}

void SessionReport::resetData()
{
    if(m_data.size()){
        m_data.clear();
        refresh();
    }
}

void SessionReport::refresh()
{
    beginResetModel();
    endResetModel();
}

QHash<int, QByteArray> SessionReport::roleNames() const
{
    return m_roleNames;
}

void SessionReport::initModel()
{
    m_roleNames[RoleName::Header_Id] = "id";
    m_roleNames[RoleName::Header_Name] = "name";
    m_roleNames[RoleName::Header_Time_Start] = "begin_session";
    m_roleNames[RoleName::Header_Time_End] = "end_session";

    resetData();

    QList<Documents::SessionReport> info = DatabaseManager::getInstanse()->getSessionReport();
    if(info.size()){
        for(auto it = info.constBegin(); it != info.end(); ++it)
        {
            SessionInfo totalDoc;
            totalDoc.id = (*it).id;
            totalDoc.name = (*it).name;
            totalDoc.beginTime = (*it).beginTime;
            totalDoc.endTime = (*it).endTime;
            m_data.push_back(totalDoc);
        }
    }
    refresh();
}
