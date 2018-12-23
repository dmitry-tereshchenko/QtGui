#ifndef AUTORIZATION_H
#define AUTORIZATION_H

#include <QObject>
#include "DatabaseManager.h"
#include "libcore/Types.h"
#include "libcore/Operator.h"

class Autorization : public QObject
{
    Q_OBJECT
public:
    explicit Autorization(QObject *parent = nullptr);
    ~Autorization();
    Q_INVOKABLE bool login(const QString& passwd);
    Q_INVOKABLE bool exit();

private:
    Operator::Info *m_info;
    bool    m_isOpenSession;
};

#endif // AUTORIZATION_H
