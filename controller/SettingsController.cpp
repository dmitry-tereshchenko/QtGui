#include "SettingsController.h"
#include "DatabaseManager.h"
#include <libJournal/Journal.h>

SettingsController::SettingsController()
    : sound(new QMediaPlayer(this))
    , timer(0)
{
    sound->setMedia(QUrl("qrc:/assets/multimedia/Sirena.mp3"));
    QObject::connect(&timer, &QTimer::timeout, [&](){sound->stop();});
}

void SettingsController::addNewUser(QString name, QString passwd, QString phone, QString level)
{
    if(DatabaseManager::getInstanse()->addNewUser(name, passwd, phone, level)){
        Journal::instance()->trace(QString("SettingsController::addNewUser() New user added"));
        emit acceptNewUser();
        return;
    }

    Journal::instance()->warning(QString("SettingsController::addNewUser() User not added"));
    emit rejectNewUser();
}

void SettingsController::play()
{
    sound->play();
    timer.start(30000); ///< 30 сек звучит сирена
}

