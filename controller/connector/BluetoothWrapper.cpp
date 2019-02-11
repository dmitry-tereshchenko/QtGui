#include "BluetoothWrapper.h"
#include "libcore/SettingsManager.h"
const QString BluetoothWrapper::uuid = "00001101-0000-1000-8000-00805F9B34FB";
const QString BluetoothWrapper::adress = SettingsManager::getInstance()->coreSettings()->value("BTAdress", "68:3e:34:f6:82:5c").toString();

BluetoothWrapper::BluetoothWrapper(QObject *parent)
    : IODevWrapper(parent)
    , m_socket(Q_NULLPTR)
    , m_localDevice(Q_NULLPTR)
    , adressLength(17)
    , type(Type::BLUETOOTH)
{
    if(adress.length() == adressLength)
    {
        m_localDevice = new QBluetoothLocalDevice(this);
        if(m_localDevice->isValid())
        {
            m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);
            connect(m_socket, SIGNAL(connected()), this, SIGNAL(deviceConnected()));
            connect(m_socket, SIGNAL(disconnected()), this, SIGNAL(deviceDisconnected()));
        }
    }
}

BluetoothWrapper::~BluetoothWrapper()
{
    if(m_socket){
        m_socket->disconnectFromService();
        m_socket->close();
        delete m_socket;
    }
    m_socket = Q_NULLPTR;
    emit deviceDisconnected();
}

QIODevice *BluetoothWrapper::device()
{
    return m_socket;
}

bool BluetoothWrapper::isOpen()
{
    return (m_socket && m_socket->isOpen());
}

bool BluetoothWrapper::open(QIODevice::OpenMode mode)
{
    if(!m_socket && !m_localDevice)
    {
        emit deviceDisconnected();
        return false;
    }
    m_localDevice->powerOn();
    m_localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
    m_socket->connectToService(QBluetoothAddress(adress), QBluetoothUuid(uuid), mode);
    emit deviceConnected();
    return true;
}

int BluetoothWrapper::getType()
{
    return type;
}

QBluetoothLocalDevice *BluetoothWrapper::getLocalDevice()
{
    return m_localDevice;
}

