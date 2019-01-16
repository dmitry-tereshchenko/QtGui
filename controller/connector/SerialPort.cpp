#include "SerialPort.h"
#include "../../libJournal/Journal.h"
#include "../../libcore/SettingsManager.h"

QHash<QString, ConcreteConnection> SerialPort::m_mapConnections;
SerialPort::SerialPort(QObject *parent)
    : QObject(parent)
    , m_device(Q_NULLPTR)
{
    init();
}

QIODevice *SerialPort::device() const
{
    return m_device->device();
}

SerialPort::~SerialPort()
{
    if(m_device)
        delete m_device;
}

bool SerialPort::openPort()
{
    QIODevice* currentDevice = m_device->device();

    if (currentDevice->isOpen())
    {
        currentDevice->reset();
        currentDevice->close();
    }

    return m_device->open(QIODevice::ReadWrite);
}

void SerialPort::closePort()
{
    QIODevice* currentDevice = m_device->device();

    if (currentDevice->isOpen())
    {
        currentDevice->close();
    }
}

bool SerialPort::isOpenPort()
{
    m_device->device()->isOpen();
}

void SerialPort::disconnected()
{
    Journal::instance()->info(QString("SerialPort::disconnected() device disconnected."));
}

void SerialPort::connected()
{
    Journal::instance()->info(QString("SerialPort::connected() device successfully opened."));
}

void SerialPort::init()
{
    m_mapConnections.insert("RS232", RS232);
    m_mapConnections.insert("WiFi", WIFI);
    m_mapConnections.insert("bluetooth", BLUETOOTH);

    const QString &connectType = SettingsManager::getInstance()->coreSettings()->value("typeConnection", "RS232").toString();

    switch (m_mapConnections[connectType]) {
        case RS232:{
            m_device = new SerialPortWrapper(this);
            break;
        }
        case WIFI:
        {
            m_device = new WiFiWrapper(this);
            break;
        }
        default: {
            Journal::instance()->error("SerialPort: unknown device type");
            Journal::instance()->warning("SerialPort: init null device");
            break;
        }
    }

    connect(m_device, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
    connect(m_device, SIGNAL(deviceConnected()), this, SIGNAL(deviceConnected()));
    connect(m_device, SIGNAL(deviceConnected()), this, SLOT(connected()));
    connect(m_device, SIGNAL(deviceDisconnected()), this, SLOT(disconnected()));
    connect(m_device, SIGNAL(deviceDisconnected()), this, SIGNAL(deviceDisconnected()));
}
