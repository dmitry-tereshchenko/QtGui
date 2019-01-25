#ifndef BLUETOOTHWRAPPER_H
#define BLUETOOTHWRAPPER_H
#include <QBluetoothSocket>
#include <QBluetoothLocalDevice>
#include "IODevWrapper.h"
#include <QObject>

class BluetoothWrapper : public IODevWrapper
{
    Q_OBJECT
public:
    BluetoothWrapper(QObject* parent);
    ~BluetoothWrapper();

    QIODevice* device();
    bool isOpen();
    bool open(QIODevice::OpenMode mode);

private:
    QBluetoothSocket*      m_socket;
    QBluetoothLocalDevice* m_localDevice;
    static const QString uuid;

private:
    const QString adress;
    const quint8 adressLength;
    const quint8 fullAdressLength;
    const QString parseAdress(QString adress);
};

#endif // BLUETOOTHWRAPPER_H
