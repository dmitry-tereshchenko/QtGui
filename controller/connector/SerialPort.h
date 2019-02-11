#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QIODevice>
#include "SerialPortWrapper.h"
#include "WiFiWrapper.h"
#include "IODevWrapper.h"
#include "BluetoothWrapper.h"

class SerialPort : public QObject
{
    Q_OBJECT
public:
    SerialPort(QObject *parent = nullptr);
    QIODevice* device() const;
    ~SerialPort();

public slots:
    bool openPort();
    void closePort();
    bool isOpenPort();

signals:
    void deviceDisconnected();
    void deviceConnected();
    void readyRead();

private:
    IODevWrapper* m_device;
    static QHash<QString, Type> m_mapConnections;

private slots:
    void init();
};

#endif // SERIALPORT_H
