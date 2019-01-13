#ifndef ENGINECONTROLLER_H
#define ENGINECONTROLLER_H

#include <QObject>
#include "Connection.h"
#include "ICommand.h"

class EngineController : public QObject
{
    Q_OBJECT
public:
    EngineController(QObject* parent = 0);
    Q_INVOKABLE void runEngine(char, uint value);
    Q_INVOKABLE void stopEngine(int);

public slots:
    const QString& read() const;

private:
    SerialPort* m_port;
    Connection* m_currentConnection;
    uchar crc8(const QByteArray &buffer);
    QByteArray toByteArray(uchar prefix, uchar postfix);
    QByteArray toByteArray(uchar summ);
};

#endif // ENGINECONTROLLER_H
