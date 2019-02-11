#ifndef SERIALPORTWRAPPER_H
#define SERIALPORTWRAPPER_H
#include "IODevWrapper.h"
#include <QSerialPort>
#include <QObject>

class SerialPortWrapper : public IODevWrapper
{
    Q_OBJECT
public:
    SerialPortWrapper(QObject* parent);
    ~SerialPortWrapper();

    QIODevice* device();
    bool isOpen();
    bool open(QIODevice::OpenMode mode);
    int getType();

private:
    QSerialPort* m_port;
    int          m_idVendor;
    int          m_idProduct;
    QString      m_portName;
    int          m_type;
};

#endif // SERIALPORTWRAPPER_H
