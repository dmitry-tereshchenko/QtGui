#include "EngineController.h"
#include <libJournal/Journal.h>

EngineController::EngineController(QObject *parent)
    : QObject(parent)
    , m_port(Q_NULLPTR)
{
    m_port = new SerialPort(this);
    QObject::connect(m_port, SIGNAL(deviceConnected()), this, SIGNAL(connectSignals()));
    QObject::connect(m_port, SIGNAL(deviceDisconnected()), this, SIGNAL(disconnectSignals()));
    QObject::connect(m_port, SIGNAL(readyRead()), this, SLOT(read()));
}

void EngineController::connect()
{
    if(m_port->openPort()){
        Journal::instance()->trace(QString("EngineController::connect() New connect"));
        return;
    }

    Journal::instance()->critical(QString("EngineController::connect() Not connect"));
}

void EngineController::disconnect()
{
    if(m_port->device()->isOpen()){
        Journal::instance()->trace(QString("EngineController::disconnect() Disconnect"));
        m_port->closePort();
        emit disconnectSignals();
    }
}

void EngineController::runEngine(int curEng, uint value)
{
    char arr[2] = {(char)curEng, (char)value};
    QString command = QString("%1%2%3").arg(static_cast<char>(curEng)).arg(value).arg(crc8(arr, sizeof(arr)));
    m_port->device()->write(command.toStdString().c_str());
    m_port->device()->waitForBytesWritten(1000);
}

void EngineController::stopEngine(int curEng)
{
    QString command = QString("%1%2").arg(static_cast<char>(curEng)).arg(0);
    m_port->device()->write(command.toStdString().c_str());
    m_port->device()->waitForBytesWritten(1000);
}

void EngineController::forceOff()
{
    QString command = QString("%1%2").arg(static_cast<char>(InputCommand::Command::Engine::ALL_ENGINES)).arg(0);
    m_port->device()->write(command.toStdString().c_str());
    m_port->device()->waitForBytesWritten(1000);
}

const QString &EngineController::read() const
{
    const QByteArray& temp = m_port->device()->readAll();
    static QString data = QString::fromStdString(temp.toStdString());
    return data;
}

uint8_t EngineController::crc8(const char *addr, uint8_t len)
{
    uint8_t crc = 0xFF;
    while (len--) {
        uint8_t inbyte = *addr++;
        for (uint8_t i = 8; i; i--) {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}
