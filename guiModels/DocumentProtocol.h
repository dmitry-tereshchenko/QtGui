#ifndef DOCUMENTPROTOCOL_H
#define DOCUMENTPROTOCOL_H

#include <QObject>
#include <QAbstractListModel>

struct DocInfo
{
    DocInfo()
        : id(0)
        , information("")
        , command(""){}

    int     id;
    QString information;
    QString command;
};

class DocumentProtocol : public QAbstractListModel
{
    Q_OBJECT

public:
    typedef QList<DocInfo> DocStruct;

    enum RoleName
    {
        Header_Id = Qt::UserRole + 1,
        Header_Information,
        Header_Command
    };

    DocumentProtocol(QObject *parent = nullptr):
        QAbstractListModel(parent){initModel();}

    virtual int rowCount(const QModelIndex& parent) const override;
    virtual QVariant data(const QModelIndex& index, int role) const override;
    Q_INVOKABLE void resetData();

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    DocStruct m_data;
    QHash<int, QByteArray> m_roleNames;
    void refresh();
    void initModel();
};

#endif // DOCUMENTPROTOCOL_H
