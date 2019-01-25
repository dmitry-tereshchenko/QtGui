#ifndef WIFIWRAPPER_H
#define WIFIWRAPPER_H

#include <QObject>
#include <QTcpSocket>
#include "IODevWrapper.h"
#include <QBluetoothSocket>
class WiFiWrapper : public IODevWrapper
{
     Q_OBJECT
public:
    WiFiWrapper(QObject* parent);
    ~WiFiWrapper();

    QIODevice* device();
    bool isOpen();
    bool open(QIODevice::OpenMode mode);

private:
    QTcpSocket* m_socket;
};

#endif // WIFIWRAPPER_H
