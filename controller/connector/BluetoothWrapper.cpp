#include "BluetoothWrapper.h"
#include "libcore/SettingsManager.h"
#include <QRegExp>

const QString BluetoothWrapper::uuid = "00001101-0000-1000-8000-00805F9B34FB";
BluetoothWrapper::BluetoothWrapper(QObject *parent)
    : IODevWrapper(parent)
    , m_socket(Q_NULLPTR)
    , m_localDevice(Q_NULLPTR)
    , adress(SettingsManager::getInstance()->coreSettings()->value("BTAdress", "").toString())
    , adressLength(12)
    , fullAdressLength(17)
{
    if(adress.length() == adressLength)
    {
        m_localDevice = new QBluetoothLocalDevice(this);
        if(m_localDevice->isValid())
        {
            m_localDevice->powerOn();
            m_localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
            m_socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol, this);

            connect(m_socket, SIGNAL(connected()), SIGNAL(deviceConnected()));
            connect(m_socket, SIGNAL(disconnected()), SIGNAL(deviceDisconnected()));
        }
    }
}

BluetoothWrapper::~BluetoothWrapper()
{
    if(m_socket){
        m_socket->close();
        delete m_socket;
        m_socket = Q_NULLPTR;
    }
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
    m_socket->connectToService(QBluetoothAddress(parseAdress(adress)), QBluetoothUuid(uuid), mode);
    if(!isOpen())
    {
        emit deviceDisconnected();
        return false;
    }
    emit deviceConnected();
    return true;
}

const QString BluetoothWrapper::parseAdress(QString adress)
{
    QRegExp rx("[0-9A-z]+");
    QString parseAdress;

    int pos = 0;
    while ((pos = rx.indexIn(adress, pos)) != -1){
        parseAdress += rx.cap(1) + ":";
        pos += rx.matchedLength();
    }

    if(parseAdress.size() == fullAdressLength + 1)
        return parseAdress.remove(fullAdressLength - 1, 1);

    return QString();
}
