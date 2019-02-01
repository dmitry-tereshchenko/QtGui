#include "CAManager.h"
#include <QStandardPaths>
#include <libJournal/Journal.h>
#include <QFile>
#ifdef QT_DEBUG
#include <QDebug>
#endif

CAManager::CAManager(QObject *parent)
    : QObject(parent)
    , m_standartPath(QStandardPaths::locate(QStandardPaths::HomeLocation, QString(), QStandardPaths::LocateDirectory))
    , m_fullPath(m_standartPath + CERT_NAME)
    , m_certData()
{
    m_certData[CAParam::CountryName] = QString("UK");
    m_certData[CAParam::OrganizationalUnitName] = QString("Children's Astronomical Observatory");
    m_certData[CAParam::LocalityName] = QString("Kramatorsk");
    m_certData[CAParam::CommonName] = QString("Tereshchenko Dmitry");
}

CAManager::~CAManager()
{
    if(m_certData.size())
        m_certData.clear();
}

void CAManager::debugDumpCertificate(const QSslCertificate &cer)
{
#ifdef QT_DEBUG
    qDebug() << ("!! =============== Ssl certificate ===============================");
    qDebug() << ("!! issuer info:");
    qDebug() << QString("Organization: ")           << cer.issuerInfo(QSslCertificate::Organization);
    qDebug() << QString("CommonName: ")             << cer.issuerInfo(QSslCertificate::CommonName);
    qDebug() << QString("LocalityName: ")           << cer.issuerInfo(QSslCertificate::LocalityName);
    qDebug() << QString("OrganizationalUnitName: ") << cer.issuerInfo(QSslCertificate::OrganizationalUnitName);
    qDebug() << QString("CountryName: ")            << cer.issuerInfo(QSslCertificate::CountryName);
    qDebug() << QString("StateOrProvinceName: ")    << cer.issuerInfo(QSslCertificate::StateOrProvinceName);
#endif
}

bool CAManager::isValidCertificate()
{
    const QSslCertificate &cert = getCertificate();
    if(!cert.issuerInfo(QSslCertificate::CountryName).size()){
        Journal::instance()->critical(QString("CAManager::isValidCertificate() Certificate not found"));
        return false;
    }

    if(cert.issuerInfo(QSslCertificate::CountryName).at(0) == m_certData[CAParam::CountryName]
            && cert.issuerInfo(QSslCertificate::OrganizationalUnitName).at(0) == m_certData[CAParam::OrganizationalUnitName]
            && cert.issuerInfo(QSslCertificate::LocalityName).at(0) == m_certData[CAParam::LocalityName]
            && cert.issuerInfo(QSslCertificate::CommonName).at(0) == m_certData[CAParam::CommonName])
    {
        if(QDateTime::currentDateTime() >= cert.effectiveDate() && QDateTime::currentDateTime() <= cert.expiryDate())
            return true;
    }

    Journal::instance()->critical(QString("CAManager::isValidCertificate() Certificate not valid"));
    return false;
}

bool CAManager::isReadNewCertificate(const QString &path)
{
    if(!QFile::exists(path))
        return false;

    QFile localCerFile(path);
    localCerFile.setPermissions(QFile::ReadOwner | QFile::WriteOwner);

    if(!localCerFile.open(QIODevice::ReadOnly))
        return false;

    const QSslCertificate cert(&localCerFile);
    if(!cert.issuerInfo(QSslCertificate::CountryName).size()){
        Journal::instance()->critical(QString("CAManager::isReadNewCertificate() Certificate not found"));
        return false;
    }

    if(cert.issuerInfo(QSslCertificate::CountryName).at(0) == m_certData[CAParam::CountryName]
            && cert.issuerInfo(QSslCertificate::OrganizationalUnitName).at(0) == m_certData[CAParam::OrganizationalUnitName]
            && cert.issuerInfo(QSslCertificate::LocalityName).at(0) == m_certData[CAParam::LocalityName]
            && cert.issuerInfo(QSslCertificate::CommonName).at(0) == m_certData[CAParam::CommonName])
    {
        if(QDateTime::currentDateTime() >= cert.effectiveDate() && QDateTime::currentDateTime() <= cert.expiryDate())
        {
            if(QFile::exists(m_fullPath))
                QFile::remove(m_fullPath);

            if(!QFile::copy(path, m_fullPath))
                return false;

            QFile::setPermissions(m_fullPath, QFile::ReadOwner | QFile::WriteOwner);
            return true;
        }
    }

    Journal::instance()->critical(QString("CAManager::isReadNewCertificate() Certificate not valid"));
    return false;
}

QSslCertificate CAManager::getCertificate() const
{
    if(!QFile::exists(m_fullPath))
        return QSslCertificate();

    QFile localCerFile(m_fullPath);
    localCerFile.setPermissions(QFile::ReadOwner | QFile::WriteOwner);

    if (!localCerFile.open(QIODevice::ReadOnly))
        return QSslCertificate();
    return QSslCertificate(&localCerFile);
}

