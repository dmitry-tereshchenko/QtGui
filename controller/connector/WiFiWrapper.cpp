#include "WiFiWrapper.h"

WiFiWrapper::WiFiWrapper(QObject *parent)
    : IODevWrapper(parent)
    , m_socket(Q_NULLPTR)
    , m_type(Type::WIFI)
{
    m_socket = new QTcpSocket(this);
    connect(m_socket, SIGNAL(connected()), SIGNAL(deviceConnected()));
    connect(m_socket, SIGNAL(disconnected()), SIGNAL(deviceDisconnected()));
    connect(m_socket, SIGNAL(readyRead()), SIGNAL(readyRead()));
}

WiFiWrapper::~WiFiWrapper()
{
    if(m_socket){
        m_socket->close();
        delete m_socket;
        m_socket = Q_NULLPTR;
    }
    emit deviceDisconnected();
}

QIODevice *WiFiWrapper::device()
{
    return m_socket;
}

bool WiFiWrapper::isOpen()
{
    return (m_socket && m_socket->isOpen());
}

bool WiFiWrapper::open(QIODevice::OpenMode mode)
{
    m_socket->connectToHost("localhost", 1929, mode);
    if(!m_socket->waitForConnected(3000))
    {
        emit deviceDisconnected();
        return false;
    }
    emit deviceConnected();
    return true;
}

int WiFiWrapper::getType()
{
    return m_type;
}
