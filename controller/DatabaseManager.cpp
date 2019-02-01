#include "DatabaseManager.h"

#include <QFile>
#include <QStandardPaths>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlError>
#include <QDateTime>

DatabaseManager::DatabaseManager()
{
    Q_ASSERT(connectToDatabase());
}

DatabaseManager::~DatabaseManager()
{
    if(db.isOpen())
        db.close();
}

DatabaseManager *DatabaseManager::getInstanse()
{
    static DatabaseManager instanse;
    return &instanse;
}

bool DatabaseManager::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    const QString databaseLocation(":/assets/database/test.sqlite");
    const QString standartPath = QString("%1%2").arg(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).arg("/.createOpticsDb");

    QDir standartPathDir(standartPath);
    if(!standartPathDir.exists())
        if(!standartPathDir.mkpath(standartPath)){
            return false;
        }

    const QString fullPath(standartPath + "/" + DATABASE_NAME);
    if(!QFile::exists(fullPath)){
        if(!QFile::copy(databaseLocation, fullPath))
            return false;
    }

    else
    {
        QFile::remove(fullPath);
        if(!QFile::copy(databaseLocation, fullPath))
            return false;
    }

    QFile::setPermissions(fullPath, QFile::WriteOwner | QFile::ReadOwner);
    db.setDatabaseName(fullPath);
    return db.open();
}

QSqlDatabase &DatabaseManager::database()
{
    return db;
}

bool DatabaseManager::addNewUser(QString name, QString passwd, QString phone, QString level)
{
    DatabaseManager::getInstanse()->transaction();

    QString phoneNumber;
    if(phone.length() > 2) ///< если больше чем "38"
        phoneNumber = phone;

    else
    {
        QSqlQuery query(db);
        query.prepare(" SELECT phone_number FROM [users] as usr "
                      " LEFT JOIN [level] as lvl "
                      "     ON lvl.id = usr.id "
                      " WHERE lvl.id = :usrLevel");

        query.bindValue(":usrLevel", Operator::Permissions::EMPLOYEE);
        if(!query.exec())
            return false;

        QSqlRecord rec = query.record();
        const int phoneAdmin = rec.indexOf("phone_number");

        if(query.first())
            phoneNumber = query.value(phoneAdmin).toString();
    }

    QSqlQuery query(db);

    query.prepare(QString("INSERT INTO "
                          " [users] "
                          " (name, phone_number, level, passwd) "
                          "     VALUES "
                          " ("
                          "     :usrName, :usrPhone, :usrLevel, :usrPasswd"
                          " ) "));

    query.bindValue(":usrName", name);
    query.bindValue(":usrPhone", phoneNumber);
    query.bindValue(":usrLevel", level.toInt());
    query.bindValue(":usrPasswd", passwd);

    if(!query.exec())
        return false;

    DatabaseManager::getInstanse()->commit();
    return true;
}

bool DatabaseManager::operatorsInfo(QList<Operator::Info> &operatorInfos)
{
    QSqlQuery query(db);

    query.prepare(QString("SELECT user.id, user.name, user.phone_number, user.level, user.passwd, level.permissions "
                          "FROM [users] as user "
                          "INNER JOIN [level] as level "
                          "ON user.level = level.id "));

    if(!query.exec())
        return false;

    QSqlRecord rec = query.record();

    const int id = rec.indexOf("id");
    const int name = rec.indexOf("name");
    const int level = rec.indexOf("level");
    const int phone = rec.indexOf("phone_number");
    const int password = rec.indexOf("passwd");
    const int permissions = rec.indexOf("permissions");

    while(query.next()){
        Operator::Info info;
        info.idOper = query.value(id).toInt();
        info.usrLevel = query.value(level).toString();
        info.usrName = query.value(name).toString();
        info.usrPhone = query.value(phone).toString();
        info.usrPassword = query.value(password).toString();
        info.permission = query.value(permissions).toString();
        operatorInfos.append(info);
    }

    return operatorInfos.count() != 0;
}

bool DatabaseManager::login(const QString& passwd, Operator::Info &info)
{
    QList<Operator::Info> operatorInfos;
    if(!operatorsInfo(operatorInfos))
        return false;

    for(auto it = operatorInfos.begin(); it != operatorInfos.end(); ++it)
        if((*it).usrPassword == passwd){
            info = *it;
            if(openSession(info))
                return true;
        }

    return false;
}

bool DatabaseManager::transaction()
{
    return db.transaction();
}

bool DatabaseManager::commit()
{
    if(!db.commit())
        return false;

    else
        return true;
}

bool DatabaseManager::openSession(Operator::Info &info)
{
    QSqlQuery query(db);
    query.setForwardOnly(true);

    QDateTime openTimeSession = QDateTime::currentDateTime();
    query.prepare(QString("INSERT INTO "
                          " [session] "
                          " (id_oper, time_start_session) "
                          "     VALUES "
                          " ("
                          "     :usrId, :startTime"
                          " ) "));

    query.bindValue(":usrId", info.getId());
    query.bindValue(":startTime", openTimeSession.toString(DATETIMESQLFORMAT));

    if(!query.exec())
        return false;

    query.prepare(QString("SELECT id FROM [session] WHERE time_start_session = :startTime"));
    query.bindValue(":startTime", openTimeSession.toString(DATETIMESQLFORMAT));

    if(!query.exec())
        return false;

    QSqlRecord rec = query.record();
    const int id = rec.indexOf("id");

    while (query.next()) {
        info.currentSession.currentUsr = info.getId();
        info.currentSession.timeCreate = openTimeSession;
        info.currentSession.id = id;
        return true;
    }

    return false;
}

bool DatabaseManager::closeSession(Operator::Info &info)
{
    QSqlQuery query(db);
    query.setForwardOnly(true);

    QDateTime closeTimeSession = QDateTime::currentDateTime();

    query.prepare(""
                  " UPDATE [session] "
                  " SET time_end_session = :stopTime "
                  " WHERE "
                  " time_start_session = :startTime ");

    query.bindValue(":startTime", info.currentSession.timeCreate.toString(DATETIMESQLFORMAT));
    query.bindValue(":stopTime", closeTimeSession.toString(DATETIMESQLFORMAT));

    if(!query.exec())
        return false;

    info.currentSession.timeClose = closeTimeSession;

    return true;
}

void DatabaseManager::getOperators(QList<QString> &operators)
{
    QSqlQuery query(db);
    query.setForwardOnly(true);

    query.prepare("SELECT level_name FROM [level]");

    if(!query.exec())
        return;

    QSqlRecord rec = query.record();
    const int id = rec.indexOf("level_name");

    while (query.next()) {
        operators.push_front(query.value(id).toString());
    }
}

QList<Documents::DocProtocolInfo> DatabaseManager::getDocProtocol()
{
    QSqlQuery query(db);
    query.setForwardOnly(true);

    query.prepare("SELECT id_protocol, information, command FROM [protocol]");

    if(!query.exec())
        return QList<Documents::DocProtocolInfo>();

    QSqlRecord rec = query.record();
    const int ix_id    = rec.indexOf("id_protocol");
    const int ix_information  = rec.indexOf("information");
    const int ix_command      = rec.indexOf("command");

    QList<Documents::DocProtocolInfo> structInfo;

    while ( query.next() )
    {
        Documents::DocProtocolInfo info;
        info.id = query.value(ix_id).toInt();
        info.information = query.value(ix_information).toString();
        info.command = query.value(ix_command).toString();
        structInfo.append(info);
    }

    return structInfo;
}

QList<Documents::SessionReport> DatabaseManager::getSessionReport()
{
    QSqlQuery query(db);
    query.setForwardOnly(true);

    query.prepare(" SELECT sessionDoc.id as id, "
                  " user.name as name, "
                  " sessionDoc.time_start_session as time_start, "
                  " sessionDoc.time_end_session as time_end "
                  "     FROM [session] as sessionDoc "
                  "         LEFT JOIN [users] as user ON sessionDoc.id_oper = user.id ");

    if(!query.exec())
        return QList<Documents::SessionReport>();

    QSqlRecord rec = query.record();
    const int ix_id    = rec.indexOf("id");
    const int ix_name  = rec.indexOf("name");
    const int ix_start = rec.indexOf("time_start");
    const int ix_end   = rec.indexOf("time_end");

    QList<Documents::SessionReport> structInfo;

    while ( query.next() )
    {
        Documents::SessionReport info;
        info.id = query.value(ix_id).toInt();
        info.name = query.value(ix_name).toString();
        info.beginTime = query.value(ix_start).toString();

        if(query.value(ix_end).toString().isEmpty())
            info.endTime = "-";
        else
            info.endTime = query.value(ix_end).toString();

        structInfo.append(info);
    }

    return structInfo;
}

