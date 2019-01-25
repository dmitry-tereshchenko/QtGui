#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <QObject>
#include "Operator.h"
#define __NOT_PERMISSIONS__ "Not permissions"

class Permissions : public QObject
{
    Q_OBJECT
    Q_ENUMS(PermissionsTypes)
public:
    Permissions(QObject *parent = Q_NULLPTR);
    enum PermissionsTypes{CAN_SETTINGS = 0, CAN_DOC, USE_CONTROL, ADD_NEW_USER};

public:
    Q_INVOKABLE bool isPermissions(const PermissionsTypes type);

private:
    bool isAddNewUser(const PermissionsTypes type);
    bool isCanDocument(const PermissionsTypes type);
    bool isControl(const PermissionsTypes type);
    bool isCanSettings(const PermissionsTypes type);
};

#endif // PERMISSIONS_H
