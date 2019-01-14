#include "Connection.h"

Connection::Connection(QObject *parent)
    : QObject(parent)
    , m_avr(IOAVR::getInstance())
{
    QObject::connect(m_avr.data(), SIGNAL(connect()), this, SIGNAL(connectChanged()));
    QObject::connect(m_avr.data(), SIGNAL(disconnect()), this, SIGNAL(disconnectChanged()));
}

void Connection::connect()
{
    if(m_avr.data()->isOpenPort()){
        Journal::instance()->trace(QString("Connection::connect() Connect to AVR"));
        emit connectChanged();
        return;
    }
    Journal::instance()->critical(QString("Connection::connect() Not connect"));
}

void Connection::disconnect()
{
    m_avr.data()->closePort();
    Journal::instance()->trace(QString("Connection::disconnect() Disconnect to AVR"));
    emit disconnectChanged();
}

