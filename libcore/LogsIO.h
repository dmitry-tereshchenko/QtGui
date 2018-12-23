#ifndef LOGSIO_H
#define LOGSIO_H

#include <QObject>

class LogsIO : public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_INVOKABLE QString read();

    explicit LogsIO(QObject *parent = nullptr);
    QString source() { return mSource; }

public slots:
    void setSource(const QString& source) {mSource = source;}

signals:
    void sourceChanged(const QString& source);

private:
    QString mSource;
};

#endif // LOGSIO_H
