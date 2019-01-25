#include "LogsIO.h"
#include <QTextStream>
#include <QFile>

LogsIO::LogsIO(QObject *parent)
    : QObject(parent)
{
}

QString LogsIO::read()
{
    if (mSource.isEmpty())
        return QString();

    QFile file(mSource);
    QString fileContent;
    if (file.open(QIODevice::ReadOnly)){
        QString line;
        QTextStream t(&file);
        do {
            line = t.readLine();
            fileContent += ("\n" + line);
        }
        while (!line.isNull());
        file.close();
    }
    else return QString();
    return fileContent;
}
