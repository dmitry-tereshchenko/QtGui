#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "controller/EngineController.h"
#include "controller/Autorization.h"
#include "controller/SettingsController.h"
#include "controller/ICommand.h"

#if defined(Q_OS_ANDROID)
#include <QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#endif
#include <libcore/SettingsManager.h>
#include <libcore/Permissions.h>
#include <libcore/LogsIO.h>
#include <guiModels/OperatorModel.h>
#include <guiModels/HeaderModel.h>
#include <guiModels/DocumentProtocol.h>
#include <libJournal/Journal.h>
#include <libJournal/JournalFile.h>
#include <libJournal/JournalSyslog.h>
#include <guiModels/SessionReport.h>
#include "Perm.h"
#include "CAManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    DatabaseManager::getInstanse();

    char b = 'x';
    int A = b;
    qDebug() <<(int)'b'<< (int)'s' << (int)'o';
    QString str = QString("%1").arg(A, 2, 16, QChar('0'));

     qDebug() << str.toLocal8Bit().toHex().toUpper();

    qmlRegisterType<EngineController>("CreateOptics", 1, 0, "Led");
    qmlRegisterType<Autorization>("CreateOptics", 1, 0, "Account");
    qmlRegisterType<SettingsController>("CreateOptics", 1, 0, "SettingsController");
    qmlRegisterType<OperatorModel>("CreateOptics", 1, 0, "OperatorModel");
    qmlRegisterType<Permissions>("CreateOptics", 1, 0, "Permissions");
    qmlRegisterType<HeaderModel>("CreateOptics", 1, 0, "HeaderModel");
    qmlRegisterType<DocumentProtocol>("CreateOptics", 1, 0, "DocumentProtocol");
    qmlRegisterType<SessionReport>("CreateOptics", 1, 0, "SessionReport");
    qmlRegisterType<CAManager>("CreateOptics", 1, 0, "CAManager");
    qmlRegisterType<LogsIO>("CreateOptics", 1, 0, "LogsIO");
    qmlRegisterType<InputCommand::Command>("CreateOptics", 1, 0, "Command");

    QQmlApplicationEngine engine;

    QString logPath = SettingsManager::getInstance()->logPath();
    Journal::instance()->addStorage(new JournalSyslog(JournalLevel::Error | JournalLevel::Critical));
    Journal::instance()->addStorage(new JournalStorage(127));
    Journal::instance()->addStorage(new JournalFile(logPath, 127));

    Permissions permissions;
    QQmlEngine::setObjectOwnership(&permissions, QQmlEngine::CppOwnership);
    engine.rootContext()->setContextProperty("permissions", &permissions);

    QString countryCode = SettingsManager::getInstance()->coreSettings()->value("Phone/phoneNumberCountryCode", "+38").toString();
    QString phoneMask = SettingsManager::getInstance()->coreSettings()->value("Phone/phoneNumberInputMask", "999 999-99-99").toString();

    int passwordLength = SettingsManager::getInstance()->coreSettings()->value("passwordLength", 5).toInt();
    int signalWarning = SettingsManager::getInstance()->guiSettings()->value("timeSirena", 1).toInt();
    bool isEnabledPhone = SettingsManager::getInstance()->coreSettings()->value("Phone/enabled", false).toBool();

    bool isEnabledBaseEngine = SettingsManager::getInstance()->coreSettings()->value("BaseEngine/enabled", false).toBool();
    int rotateCountBaseEngine = SettingsManager::getInstance()->coreSettings()->value("BaseEngine/rotateCount", 10).toInt();
    double stepSizeBaseEngine = SettingsManager::getInstance()->coreSettings()->value("BaseEngine/stepSize", 1).toDouble();

    bool isEnabledSecondaryEngine = SettingsManager::getInstance()->coreSettings()->value("SecondaryEngines/enabled", false).toBool();
    int rotateCountSecondaryEngine = SettingsManager::getInstance()->coreSettings()->value("SecondaryEngines/rotateCount", 10).toInt();
    double stepSizeSecondaryEngine = SettingsManager::getInstance()->coreSettings()->value("SecondaryEngines/stepSize", 1).toDouble();

    engine.rootContext()->setContextProperty("countryCode", countryCode);
    engine.rootContext()->setContextProperty("phoneMask", phoneMask);
    engine.rootContext()->setContextProperty("passwordLength", passwordLength);
    engine.rootContext()->setContextProperty("isEnabledPhone", isEnabledPhone);
    engine.rootContext()->setContextProperty("signalWarning", signalWarning);
    engine.rootContext()->setContextProperty("signalWarning", signalWarning);
    engine.rootContext()->setContextProperty("logPath", logPath);
    /*
     * Настройки главного двигателя
     */

    /* -----------------------------------------------------------------------------------*/
    engine.rootContext()->setContextProperty("isEnabledBaseEngine", isEnabledBaseEngine);
    engine.rootContext()->setContextProperty("rotateCountBaseEngine", rotateCountBaseEngine);
    engine.rootContext()->setContextProperty("stepSizeBaseEngine", stepSizeBaseEngine);
    /* -----------------------------------------------------------------------------------*/

    /*
     * Настройки вторичных двигателей
     */

    /* -----------------------------------------------------------------------------------*/
    engine.rootContext()->setContextProperty("isEnabledSecondaryEngine", isEnabledSecondaryEngine);
    engine.rootContext()->setContextProperty("rotateCountSecondaryEngine", rotateCountSecondaryEngine);
    engine.rootContext()->setContextProperty("stepSizeSecondaryEngine", stepSizeSecondaryEngine);
    /* -----------------------------------------------------------------------------------*/

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
