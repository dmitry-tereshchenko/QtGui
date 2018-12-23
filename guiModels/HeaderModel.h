#ifndef HEADERMODEL_H
#define HEADERMODEL_H

#include <QObject>
#include <QPair>
#include <QMap>
#include <QAbstractListModel>

class HeaderModel : public QAbstractListModel
{
    Q_OBJECT
    enum Roles
    {
        Header_Image = Qt::UserRole + 1,
        Header_Name
    };

Q_ENUMS(Name)

public:
    QList<QPair<QString, QString>> m_typeHeader;
    enum Name{
        MENU,
        HOME,
        DOCUMENTS,
        CONTROL,
        SETTINGS,
        LOGOUT
    };
    QMap<QString, Name> m_map;

    HeaderModel(QObject *parent = nullptr):
        QAbstractListModel(parent){initModel();}

    int rowCount(const QModelIndex &parent) const {Q_UNUSED(parent); return m_typeHeader.count();}
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;


private:
   void initModel();
};

#endif // HEADERMODEL_H
