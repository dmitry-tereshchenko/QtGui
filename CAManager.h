#ifndef CAMANAGER_H
#define CAMANAGER_H

#include <QSslCertificate>
#include <QObject>

#define CERT_NAME "rootCA.pem"

class CAManager : public QObject
{
    Q_OBJECT
public:
    enum CAParam{
        CommonName,
        LocalityName,
        OrganizationalUnitName,
        CountryName
    };

    explicit CAManager(QObject* parent = 0);
    ~CAManager();

    Q_INVOKABLE bool isValidCertificate();
    Q_INVOKABLE bool isReadNewCertificate(const QString& path);

private:
    static void debugDumpCertificate(const QSslCertificate& cer);
    QSslCertificate getCertificate() const;

private:
    //const QString          m_certLocation;
    const QString          m_standartPath;
    const QString          m_fullPath;
    QMap<CAParam, QString> m_certData;
};

#endif // CAMANAGER_H
