#include "Perm.h"
#include <QGuiApplication>
#include <unistd.h>

Perm::Perm(QObject *parent)
    : QObject(parent)
    , m_permissionWasGranted(Unknown)
{
}

Perm::Perms Perm::requestPermissions()
{
#if defined(Q_OS_ANDROID)
    if (getIsMarshmallowOrAbove())
    {
        m_requestPermissions = QAndroidJniObject("src/org/RequestPermissions",
                                                 "(Landroid/app/Activity;)V",
                                                 QtAndroid::androidActivity().object<jobject>()
                                                 );
        QAndroidJniEnvironment env;
        if (env->ExceptionCheck()) {
            env->ExceptionClear();

        }
        m_permissionWasGranted = Unknown;  // Unclear if the permission has been granted
        while(m_permissionWasGranted == Unknown)
        {
            verifyPermissionState();
            sleep(1);
            QGuiApplication::processEvents();
        }
        return m_permissionWasGranted;
    }
    m_permissionWasGranted = Granted;
    return Granted;
#else

    return Granted;

#endif

}

void Perm::verifyPermissionState()
{
#if defined(Q_OS_ANDROID)
    QString permissionState;
    QAndroidJniObject stringResult = QAndroidJniObject::callStaticObjectMethod("src/org/RequestPermissions",
                                                                               "getResponseState",
                                                                               "()Ljava/lang/String;");
    QAndroidJniEnvironment env;
    if (env->ExceptionCheck()) {
        env->ExceptionClear();
    }

    permissionState = stringResult.toString();
    if (permissionState == "Granted" || (permissionState == "Just Granted"))
    {
        m_permissionWasGranted = Granted;
        QGuiApplication::processEvents();
    }

    else if ((permissionState == "Denied"))
    {
        m_permissionWasGranted = Denied;
        QGuiApplication::processEvents();
    }

#else

    m_permissionWasGranted = Granted;

    QGuiApplication::processEvents();

#endif
}

bool Perm::getIsMarshmallowOrAbove()
{
#if defined(Q_OS_ANDROID)
    QAndroidJniObject result = QAndroidJniObject::callStaticObjectMethod("src/org/RequestPermissions",
                                                                               "getSdkVersion",
                                                                               "()Ljava/lang/String;");
    QAndroidJniEnvironment env;
    if (env->ExceptionCheck())
    {
        env->ExceptionClear();
    }

    enum SdkVersion
    {
        Marshmallow = 23
    };

    if(result.toString().toInt() < Marshmallow)
    {
        m_permissionWasGranted = Granted;
        return false;
    }
    return true;
#else

    return false;

#endif

}

Perm::Perms Perm::getPermissionGranted()
{
    return m_permissionWasGranted;
}
