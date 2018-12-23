#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSaveFile>
#include <QSqlDatabase>
#include "libcore/Types.h"

#include <QDir>
#include <QDebug>
#include <QFile>

#define DATABASE_NAME "test.sqlite"

class DatabaseManager
{
public:
    static DatabaseManager* getInstanse();
    QSqlDatabase& database();
    bool addNewUser(QString name, QString passwd, QString phone, QString level);
    bool operatorsInfo(QList<Operator::Info>& operatorInfos);
    bool login(const QString &passwd, Operator::Info &info);

    bool transaction();
    bool commit();
    bool openSession(Operator::Info &info);
    bool closeSession(Operator::Info &info);
    void getOperators(QList<QString>& operators);

    QList<Documents::DocProtocolInfo> getDocProtocol();
    QList<Documents::SessionReport> getSessionReport();

private:
    QSqlDatabase db;
    DatabaseManager();
    ~DatabaseManager();
    bool connectToDatabase();
};

#endif // DATABASEMANAGER_H
