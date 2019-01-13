#include "Autorization.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <libJournal/Journal.h>

Autorization::Autorization(QObject *parent)
    : QObject(parent)
    , m_isOpenSession(false)
{
}

Autorization::~Autorization()
{
    if(m_isOpenSession)
        exit();
}

bool Autorization::login(const QString& passwd)
{
    if(passwd != m_info.getPassword()){
        exit();
        if(!DatabaseManager::getInstanse()->login(passwd, m_info)){
            Journal::instance()->error(QString("Autorization::login() Wrong password!"));
            return false;
        }
    }

    Operator::setOperator(m_info);
    Journal::instance()->trace(QString("Start session!"));
    Journal::instance()->trace(QString("Autorization::login() User: %1").arg(m_info.usrName));
    m_isOpenSession = true;
    return true;
}

bool Autorization::exit()
{
    if(DatabaseManager::getInstanse()->closeSession(m_info)){
        Journal::instance()->trace(QString("End session!"));
        return true;
    }

    return false;
}

Operator::Info::Info():
    idOper     (INVALID_OPERATOR_ID),
    usrName       (""),
    usrLevel      (""),
    usrPhone      (""),
    usrPassword   (""),
    permission    ("")
{

}

Operator::Info::Info(const Info& obj):
    idOper      (obj.idOper      ),
    usrName     (obj.usrName     ),
    usrLevel    (obj.usrLevel    ),
    usrPhone    (obj.usrPhone    ),
    usrPassword (obj.usrPassword ),
    permission  (obj.permission  )
{
    //
}

Operator::Info& Operator::Info::operator=(const Info& obj)
{
    if(this != &obj)
    {
        this->~Info();
        new(this) Info(obj);
    }
    return *this;
}

Operator::Info::~Info()
{
    //
}

Operator::Id Operator::Info::getId() const
{
    return idOper;
}

//QString Operator::Info::getName() const
//{
//    return usrName;
//}

QString Operator::Info::getPhone() const
{
    return usrPhone;
}

QString Operator::Info::getLevel() const
{
    return usrLevel;
}

QString Operator::Info::getPassword() const
{
    return usrPassword;
}

QString Operator::Info::getPermissions() const
{
    return permission;
}

bool Operator::Info::isValid() const
{
    return INVALID_OPERATOR_ID != idOper;
}

bool Operator::Info::operator==(const Operator::Info &obj) const
{
    return this == &obj ? true : obj.getId() == idOper;
}
