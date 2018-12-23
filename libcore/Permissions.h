#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <QObject>
#include "Operator.h"
class Permissions : public QObject
{
    Q_OBJECT
public:
    Permissions(QObject *parent = nullptr);

public slots:
    Q_INVOKABLE bool isAddNewUser();
    Q_INVOKABLE bool isCanDocument();
    Q_INVOKABLE bool isControl();
    Q_INVOKABLE bool isCanSettings();

signals:
    void noPermissionsSignal();
};

#endif // PERMISSIONS_H
