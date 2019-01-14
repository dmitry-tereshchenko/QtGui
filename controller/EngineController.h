#ifndef ENGINECONTROLLER_H
#define ENGINECONTROLLER_H

#include <QObject>
#include "connector/IOAVR.h"
#include "ICommand.h"

class EngineController : public QObject
{
    Q_OBJECT
public:
    EngineController(QObject* parent = 0);
    Q_INVOKABLE void runEngine(char, uint value);

public slots:
    const QString& read() const;

private:
    SerialPort* m_port;
    IOAVR* m_currentConnection;
    QByteArray toByteArray(uchar prefix, uchar postfix);
};

#endif // ENGINECONTROLLER_H
