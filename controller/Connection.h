#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include "connector/SerialPort.h"
#include <libJournal/Journal.h>

class Connection : public QObject
{
    Q_OBJECT
public:
    static Connection* getInstance();
    Q_INVOKABLE void connect();
    Q_INVOKABLE void disconnect();

    bool isOpentPort() const;
    SerialPort* getPort() const;

signals:
    void connectChanged();
    void disconnectChanged();
    void readChanged();

private:
    Connection(QObject *parent = nullptr);
    SerialPort* m_port;
    bool        m_isOpenPort;

public slots:
};


#endif // CONNECTION_H
