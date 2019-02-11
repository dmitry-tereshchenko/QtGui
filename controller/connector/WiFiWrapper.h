#ifndef WIFIWRAPPER_H
#define WIFIWRAPPER_H

#include <QObject>
#include <QTcpSocket>
#include "IODevWrapper.h"

class WiFiWrapper : public IODevWrapper
{
     Q_OBJECT
public:
    WiFiWrapper(QObject* parent);
    ~WiFiWrapper();

    QIODevice* device();
    bool isOpen();
    bool open(QIODevice::OpenMode mode);
    int getType();

private:
    QTcpSocket* m_socket;
    int         m_type;
};

#endif // WIFIWRAPPER_H
