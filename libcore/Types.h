#ifndef TYPES_H
#define TYPES_H
#include <QString>
#include <QDateTime>
/**
 * Формат даты и времени для SQL (sqlite3)
 */
#define DATETIMESQLFORMAT "yyyy-MM-ddTHH:mm:ss"

#define MAX_VALUE_ENGINE 255

#define INVALID_OPERATOR_ID -1 ///< Невалидный идентификатор оператора, устанавливающийся в конструкторе по умолчанию

/*!
 * Идентификатор сессии
 */
typedef int SessionId;

namespace Documents {
    struct DocProtocolInfo
    {
        int     id;
        QString information;
        QString command;
    };

    struct SessionReport
    {
        SessionReport()
            : id(0)
            , name("")
            , beginTime("")
            , endTime(""){}

        int     id;
        QString name;
        QString beginTime;
        QString endTime;
    };
}

namespace Operator {

enum Permissions{
    STUDENT = 1, ///< Ученик
    EMPLOYEE = 2, ///< Рабочий
    ADMINISTRATOR = 3, ///< Администратор
    MASTER = 4 ///< Мастер
};

enum PermissionsList{
    ENTER_TO_SETTINGS = 0,
    CAN_DOC,
    ENGINES_CONTROL,
    ADD_NEW_USERS
};

/*
     * Определение типа идентификатора операторов.
     */
typedef int Id;

class Info
{
public:
    Id      idOper;
    QString usrName;
    QString usrLevel;
    QString usrPhone;
    QString usrPassword;
    QString permission; ///< Разрешения оператора

public:

    struct Session{
        SessionId id;
        Id        currentUsr;
        QDateTime timeCreate;
        QDateTime timeClose;
        Session() : id(-1), currentUsr(INVALID_OPERATOR_ID){}
    };

    Session currentSession;
    Info();
    Info(const Info& obj);
    Info& operator=(const Info& obj);
    ~Info();

    Id getId() const;                       ///< Метод возвращающий идентификатор оператора
    QString getName() const;                ///< Метод возвращающий имя оператора
    QString getPhone() const;
    QString getLevel() const;
    QString getPassword() const;
    QString getPermissions() const;
    bool isValid() const;                   ///< Метод проверки оператора на валидность
    bool operator==(const Info& obj) const; ///Метод сравнения операторов
};

}

#endif // TYPES_H
