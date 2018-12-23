#ifndef DEFAULTSFILEPATH_H
#define DEFAULTSFILEPATH_H
#include <QString>

struct DefaultsFilePath
{
    /**
     * @brief Файл с настройками для GUI
     */
    static QString guiSettingsFile();

    /**
     * @brief Файл с настройками для ядра
     */
    static QString coreSettingsFile();
};

#endif // DEFAULTSFILEPATH_H
