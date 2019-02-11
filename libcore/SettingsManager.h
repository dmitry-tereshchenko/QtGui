#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <QSettings>

class SettingsManager
{
private:
    QSettings*  m_guiSettings;
    QSettings*  m_coreSettings;

protected:
    SettingsManager();

public:
    static SettingsManager* getInstance();
    ~SettingsManager();

    QSettings*  guiSettings();
    QSettings*  coreSettings();
    QString     logPath();
};

#endif // SETTINGSMANAGER_H
