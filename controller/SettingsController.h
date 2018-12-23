#ifndef SETTINGSCONTROLLER_H
#define SETTINGSCONTROLLER_H
#include <QObject>
#include "libcore/Types.h"
#include <QMediaPlayer>
#include <QTimer>

class SettingsController : public QObject
{
    Q_OBJECT
public:
    SettingsController();
    Q_INVOKABLE void addNewUser(QString name, QString passwd, QString phone, QString level);

public slots:
    Q_INVOKABLE void play();

signals:
    void acceptNewUser();
    void rejectNewUser();

private:
    QMediaPlayer* sound;
    QTimer        timer;
};

#endif // SETTINGSCONTROLLER_H
