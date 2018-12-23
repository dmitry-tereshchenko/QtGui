#pragma once

#include <QObject>
#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QtAndroid>
#endif

class Perm : public QObject
{
    Q_OBJECT
public:
    enum Perms
        {
        Unknown = 0,
        Granted = 1,
        Denied  = 2
    };
    Q_ENUMS(Perms)
    explicit Perm(QObject *parent = 0);

    Q_INVOKABLE Perms requestPermissions();
    Q_INVOKABLE Perms getPermissionGranted();
    Q_INVOKABLE bool getIsMarshmallowOrAbove();

private slots:
    void verifyPermissionState();

private:

#if defined(Q_OS_ANDROID)
    QAndroidJniObject m_requestPermissions;

#endif
    Perms m_permissionWasGranted;

};
