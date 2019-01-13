#include "Connection.h"
#include <functional>

Connection::Connection(QObject *parent)
    : QObject(parent)
    , m_port(Q_NULLPTR)
    , m_isOpenPort(false)
{
    m_port = new SerialPort(this);
    QObject::connect(m_port, SIGNAL(deviceConnected()), this, SIGNAL(connectChanged()));
    QObject::connect(m_port, SIGNAL(deviceDisconnected()), this, SIGNAL(disconnectChanged()));
    QObject::connect(m_port, SIGNAL(readyRead()), this, SIGNAL(readChanged()));
}

Connection *Connection::getInstance()
{
    static Connection instance;
    return &instance;
}

void Connection::connect()
{
    if(m_port->openPort()){
        Journal::instance()->trace(QString("EngineController::connect() New connect"));
        m_isOpenPort = true;
        emit connectChanged();
        return;
    }
    Journal::instance()->critical(QString("EngineController::connect() Not connect"));
}

void Connection::disconnect()
{
    if(isOpentPort()){
        Journal::instance()->trace(QString("EngineController::disconnect() Disconnect"));
        m_port->closePort();
        emit disconnectChanged();
    }
}

bool Connection::isOpentPort() const
{
    return m_isOpenPort;
}

SerialPort *Connection::getPort() const
{
    return m_port;
}
