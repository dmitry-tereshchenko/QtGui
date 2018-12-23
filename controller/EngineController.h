#ifndef ENGINECONTROLLER_H
#define ENGINECONTROLLER_H

#include <QObject>
#include <libcore/Types.h>
#include "connector/SerialPort.h"
#include "ICommand.h"

class EngineController : public QObject
{
    Q_OBJECT
public:
    EngineController(QObject* parent = 0);
    Q_INVOKABLE void connect();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void runEngine(int, uint value);
    Q_INVOKABLE void stopEngine(int);
    Q_INVOKABLE void forceOff();

signals:
    void connectSignals();
    void disconnectSignals();

public slots:
    const QString& read() const;

private:
    SerialPort* m_port;
    char crc8(const QByteArray &buffer);
};

#endif // ENGINECONTROLLER_H
