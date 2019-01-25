#include "Connection.h"

Connection::Connection(QObject *parent)
    : QObject(parent)
    , m_avr(IOAVR::getInstance())
{
    QObject::connect(m_avr, SIGNAL(connect()), this, SIGNAL(connectChanged()));
    QObject::connect(m_avr, SIGNAL(disconnect()), this, SIGNAL(disconnectChanged()));
}

void Connection::connect()
{
    if(m_avr->openPort()){
        Journal::instance()->trace(QString("Connection::connect() Connect to AVR"));
        emit connectChanged();
        return;
    }
    Journal::instance()->critical(QString("Connection::connect() Not connect"));
}

void Connection::disconnect()
{
    m_avr->closePort();
    Journal::instance()->trace(QString("Connection::disconnect() Disconnect to AVR"));
    emit disconnectChanged();
}

