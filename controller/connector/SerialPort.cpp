#include "SerialPort.h"
#include "../../libJournal/Journal.h"
#include "../../libcore/SettingsManager.h"

QHash<QString, Type> SerialPort::m_mapConnections;
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
    m_device = Q_NULLPTR;
}

bool SerialPort::openPort()
{
    QIODevice* currentDevice = m_device->device();
    if (currentDevice && m_device->isOpen())
    {
        currentDevice->reset();
        currentDevice->close();
    }
    return m_device->open(QIODevice::ReadWrite);
}

void SerialPort::closePort()
{
    QIODevice* currentDevice = m_device->device();
    if (currentDevice && currentDevice->isOpen())
    {
        #if defined(Q_OS_ANDROID)
        if(m_device->getType() == Type::BLUETOOTH)
        {
            BluetoothWrapper* bluetoothDevice = static_cast<BluetoothWrapper*>(m_device);
            bluetoothDevice->getLocalDevice()->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
        }
        #endif
        currentDevice->close();
    }
}

bool SerialPort::isOpenPort()
{
    return m_device->device()->isOpen();
}

void SerialPort::init()
{
    m_mapConnections.insert("RS232", Type::RS232);
    m_mapConnections.insert("WiFi", Type::WIFI);
    m_mapConnections.insert("bluetooth", Type::BLUETOOTH);

    const QString &connectType = SettingsManager::getInstance()->coreSettings()->value("typeConnection", "RS232").toString();

    switch (m_mapConnections[connectType])
    {
        case Type::RS232:{
            m_device = new SerialPortWrapper(this);
            break;
        }
        case Type::WIFI:
        {
            m_device = new WiFiWrapper(this);
            break;
        }
        case Type::BLUETOOTH:
        {
        #if defined(Q_OS_ANDROID)
            m_device = new BluetoothWrapper(this);
            break;
        #endif
            Journal::instance()->error("SerialPort::init() bluetooth not found");
            break;
        }
        default: {
            Journal::instance()->error("SerialPort::init() unknown device type");
            break;
        }
    }

    connect(m_device, SIGNAL(readyRead()), this, SIGNAL(readyRead()));
    connect(m_device, SIGNAL(deviceConnected()), this, SIGNAL(deviceConnected()));
    connect(m_device, SIGNAL(deviceDisconnected()), this, SIGNAL(deviceDisconnected()));
}
