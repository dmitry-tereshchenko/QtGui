#include "Permissions.h"
#include <libJournal/Journal.h>

Permissions::Permissions(QObject *parent) : QObject(parent)
{

}

bool Permissions::isAddNewUser()
{
    if(!Operator::can(Operator::PermissionsList::ADD_NEW_USERS)){
        Journal::instance()->warning(QString("Permissions::isAddNewUser() Not permissions"));
        emit noPermissionsSignal();
        return false;
    }
    return true;
}

bool Permissions::isCanDocument()
{
    if(!Operator::can(Operator::PermissionsList::CAN_DOC)){
        Journal::instance()->warning(QString("Permissions::isCanDocument() Not permissions"));
        emit noPermissionsSignal();
        return false;
    }
    return true;
}

bool Permissions::isControl()
{
    if(!Operator::can(Operator::PermissionsList::ENGINES_CONTROL)){
        Journal::instance()->warning(QString("Permissions::isControl() Not permissions"));
        emit noPermissionsSignal();
        return false;
}
    return true;
}

bool Permissions::isCanSettings()
{
    if(!Operator::can(Operator::PermissionsList::ENTER_TO_SETTINGS)){
        Journal::instance()->warning(QString("Permissions::isCanSettings() Not permissions"));
        emit noPermissionsSignal();
        return false;
    }
    return true;
}
