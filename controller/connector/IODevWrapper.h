#ifndef IODEVWRAPPER_H
#define IODEVWRAPPER_H

#include <QObject>
#include <QIODevice>
#include "libcore/Types.h"

typedef Connect::ConnectionType Type;
class IODevWrapper : public QObject
{
    Q_OBJECT
public:
    IODevWrapper(QObject* parent = 0);
    virtual ~IODevWrapper();
    virtual QIODevice* device() = 0;
    virtual bool isOpen() = 0;
    virtual bool open(QIODevice::OpenMode mode = QIODevice::ReadWrite) = 0;
    virtual int getType() = 0;

signals:
    void deviceDisconnected();
    void deviceConnected();
    void readyRead();
};

#endif // IODEVWRAPPER_H
