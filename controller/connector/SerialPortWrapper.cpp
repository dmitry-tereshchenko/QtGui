#include <QSerialPortInfo>
#include "SerialPortWrapper.h"
#include "../../libcore/SettingsManager.h"

SerialPortWrapper::SerialPortWrapper(QObject* parent)
    : IODevWrapper(parent)
    , m_port(Q_NULLPTR)
    , m_idVendor(0)
    , m_idProduct(0)
    , m_portName("")
{
    m_idVendor = SettingsManager::getInstance()->coreSettings()->value("idVendor", 0).toInt();
    m_idProduct = SettingsManager::getInstance()->coreSettings()->value("idProduct", 0).toInt();

    m_port = new QSerialPort(this);
    connect(m_port, SIGNAL(readyRead()), SIGNAL(readyRead()));
}

SerialPortWrapper::~SerialPortWrapper()
{
    if(m_port){
        m_port->close();
        delete m_port;
    }
    m_port = Q_NULLPTR;
    emit deviceDisconnected();
}

QIODevice *SerialPortWrapper::device()
{
    return m_port;
}

bool SerialPortWrapper::isOpen()
{
    return (m_port && m_port->isOpen());
}

bool SerialPortWrapper::open(QIODevice::OpenMode mode)
{
    bool status = false;
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if(serialPortInfo.vendorIdentifier() == m_idVendor){
            if(serialPortInfo.productIdentifier() == m_idProduct){
                m_portName = serialPortInfo.portName();
                status = true;
            }
        }
    }

    if(!status){
        emit deviceDisconnected();
        return false;
    }

    m_port->setPortName(m_portName);
    QObject::connect(m_port, SIGNAL(readyRead()), this, SIGNAL(readyRead()), Qt::QueuedConnection);

    if(m_port->open(mode))
    {
        const int& baudRate = SettingsManager::getInstance()->coreSettings()->value("General/baudRate", 9600).toInt();
        switch (baudRate) {
        case 9600: {m_port->setBaudRate(QSerialPort::Baud9600); break;}
        case 4800: {m_port->setBaudRate(QSerialPort::Baud4800); break;}
        case 115200: {m_port->setBaudRate(QSerialPort::Baud115200); break;}
        default: break;
        }

        m_port->setDataBits(QSerialPort::Data8);
        m_port->setParity(QSerialPort::NoParity);
        m_port->setStopBits(QSerialPort::OneStop);
        m_port->setFlowControl(QSerialPort::NoFlowControl);
        emit deviceConnected();
        return true;
    }
    emit deviceDisconnected();
    return false;
}
