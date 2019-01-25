#include "EngineController.h"
#include<QDataStream>

EngineController::EngineController(QObject *parent)
    : QObject(parent)
    , m_currentConnection(IOAVR::getInstance())
{
}

QByteArray EngineController::toByteArray(uchar symbol)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << symbol;
    return array;
}

void EngineController::runEngine(char curEng, uint value)
{
    QByteArray command;
    command += toByteArray((uchar)curEng);
    command += toByteArray((uchar)value);

    m_currentConnection->write(command);
}

const QString &EngineController::read() const
{
//     qDebug() << "Read: ";
//    const QByteArray& temp = m_port->device()->readAll();
//    static QString data = QString::fromStdString(temp.toStdString());
//    qDebug() << "Data: " << data;
//    return data;
}
