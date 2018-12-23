#ifndef SESSIONREPORT_H
#define SESSIONREPORT_H

#include <QObject>
#include <QAbstractListModel>

struct SessionInfo
{
    SessionInfo()
        : id(0)
        , name("")
        , beginTime("")
        , endTime(""){}

    int     id;
    QString name;
    QString beginTime;
    QString endTime;
};

class SessionReport : public QAbstractListModel
{
    Q_OBJECT
public:
    typedef QList<SessionInfo> DocStruct;

    enum RoleName
    {
        Header_Id = Qt::UserRole + 1,
        Header_Name,
        Header_Time_Start,
        Header_Time_End
    };

    SessionReport(QObject *parent = nullptr):
        QAbstractListModel(parent){initModel();}

    virtual int rowCount(const QModelIndex& parent) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;
    Q_INVOKABLE void resetData();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    DocStruct m_data;
    QHash<int, QByteArray> m_roleNames;
    void refresh();
    void initModel();
};

#endif // SESSIONREPORT_H
