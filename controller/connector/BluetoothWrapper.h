#ifndef BLUETOOTHWRAPPER_H
#define BLUETOOTHWRAPPER_H
#include <QBluetoothSocket>
#include <QBluetoothLocalDevice>
#include "IODevWrapper.h"

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

private:
    const quint8  adressLength;
    static const QString uuid;
    static const QString adress;
};

#endif // BLUETOOTHWRAPPER_H
