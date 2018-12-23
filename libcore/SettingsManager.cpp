#include "SettingsManager.h"
#include "DefaultsFilePath.h"
#include <QStandardPaths>
#include <QFile>
#include <QDir>

SettingsManager* SettingsManager::p_instance = Q_NULLPTR;
SettingsManager::SettingsManager()
    : m_guiSettings(Q_NULLPTR)
    , m_coreSettings(Q_NULLPTR)
{

}

SettingsManager::~SettingsManager(){
    if(m_guiSettings)
        delete m_guiSettings;

    if(m_coreSettings)
        delete m_coreSettings;

    delete p_instance;
}

SettingsManager* SettingsManager::getInstance() {
    if ( !p_instance )
        p_instance = new SettingsManager();

    return p_instance;
}

QSettings* SettingsManager::guiSettings()
{
    if (!m_guiSettings)
    {
        if ( QFile::exists(DefaultsFilePath::guiSettingsFile()) )
        {
            m_guiSettings = new QSettings(DefaultsFilePath::guiSettingsFile(), QSettings::IniFormat);
            m_guiSettings->setIniCodec("UTF-8");
        }

        else
            m_guiSettings = new QSettings();
    }
    return m_guiSettings;
}

QSettings* SettingsManager::coreSettings(){
    if (!m_coreSettings)
    {
        if ( QFile::exists(DefaultsFilePath::coreSettingsFile()) )
        {
            m_coreSettings = new QSettings(DefaultsFilePath::coreSettingsFile(), QSettings::IniFormat);
            m_coreSettings->setIniCodec("UTF-8");
        }

        else
            m_coreSettings = new QSettings();
    }
    return m_coreSettings;
}

QString SettingsManager::logPath()
{
    const QString standartPath = QString("%1%2").arg(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).arg("/.logs");

    QDir standartPathDir(standartPath);
    if(!standartPathDir.exists())
        if(!standartPathDir.mkpath(standartPath)){
            return QString();
        }

    QFile fileLog(standartPath + QString("/log.txt"));
    if (fileLog.open(QIODevice::WriteOnly | QIODevice::Append)) {
        fileLog.close();
        return standartPath + "/log.txt";
    }

    return QString();
}
