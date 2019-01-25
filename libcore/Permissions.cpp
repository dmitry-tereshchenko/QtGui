#include "Permissions.h"
#include <libJournal/Journal.h>

Permissions::Permissions(QObject *parent) : QObject(parent)
{
}

bool Permissions::isAddNewUser(const PermissionsTypes type)
{
    if(!Operator::can(type)){
        Journal::instance()->warning(QString("%1 %2").arg(__PRETTY_FUNCTION__).arg(__NOT_PERMISSIONS__));
        return false;
    }
    return true;
}

bool Permissions::isCanDocument(const PermissionsTypes type)
{
    if(!Operator::can(type)){
        Journal::instance()->warning(QString("%1 %2").arg(__PRETTY_FUNCTION__).arg(__NOT_PERMISSIONS__));
        return false;
    }
    return true;
}

bool Permissions::isControl(const PermissionsTypes type)
{
    if(!Operator::can(type)){
        Journal::instance()->warning(QString("%1 %2").arg(__PRETTY_FUNCTION__).arg(__NOT_PERMISSIONS__));
        return false;
}
    return true;
}

bool Permissions::isCanSettings(const PermissionsTypes type)
{
    if(!Operator::can(type)){
        Journal::instance()->warning(QString("%1 %2").arg(__PRETTY_FUNCTION__).arg(__NOT_PERMISSIONS__));
        return false;
    }
    return true;
}

bool Permissions::isPermissions(const PermissionsTypes type)
{
    switch (type) {
    case ADD_NEW_USER: {return isAddNewUser(type);}
    case CAN_SETTINGS: {return isCanSettings(type);}
    case USE_CONTROL: {return isControl(type);}
    case CAN_DOC: {return isCanDocument(type);}
    default: return false;
    }
    return false;
}
