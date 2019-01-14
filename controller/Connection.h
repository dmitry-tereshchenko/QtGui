#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "connector/SerialPort.h"
#include "libJournal/Journal.h"
#include "connector/IOAVR.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection(QObject *parent = nullptr);

    Q_INVOKABLE void connect();
    Q_INVOKABLE void disconnect();

signals:
    void connectChanged();
    void disconnectChanged();

private:
    QScopedPointer<IOAVR> m_avr;
};


#endif // CONNECTION_H
