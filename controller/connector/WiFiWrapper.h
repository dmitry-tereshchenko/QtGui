#ifndef WIFIWRAPPER_H
#define WIFIWRAPPER_H

#include <QObject>
#include <QTcpSocket>
#include "IODevWrapper.h"

class WiFiWrapper : public IODevWrapper
{
     Q_GADGET
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
