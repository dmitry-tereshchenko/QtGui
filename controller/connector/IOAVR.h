#ifndef IOAVR_H
#define IOAVR_H

#include <QDataStream>
#include <QObject>
#include <QMutex>
#include "SerialPort.h"

#define MAX_TIMEOUT 500
class IOAVR : public QObject
{
    Q_OBJECT
public:
    static IOAVR* getInstance();

signals:
    void connect();
    void disconnect();
    void readyRead();

public:
    void write(const QByteArray& command);
    bool openPort();
    bool isOpenPort();
    void closePort();

private:
    IOAVR(QObject *parent = nullptr);
    IOAVR(const IOAVR&) = delete;
    IOAVR& operator=(IOAVR&) = delete;

    SerialPort*                p_port;
    static QMutex              mutex;

private:
    uchar      crc8(const QByteArray &buffer);
    QByteArray toByteArray(uchar summ);
    bool       isChecked();
};

#endif // IOAVR_H
