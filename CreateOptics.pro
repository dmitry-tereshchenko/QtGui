QT += bluetooth sql \
    qml \
    quick \
    serialport \
    multimedia \
    network \
    charts

CONFIG += c++11 \
          mobility

MOBILITY = connectivity

TRANSLATIONS = translations/en.ts\
    translations/uk.ts \
    translations/ru.ts

#QT += androidextras
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

COMMON_DATA.path = /assets
COMMON_DATA.files = /assets
INSTALLS += COMMON_DATA

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

SOURCES += main.cpp \
    controller/DatabaseManager.cpp \
    controller/Autorization.cpp \
    controller/SettingsController.cpp \
    controller/EngineController.cpp \
    guiModels/OperatorModel.cpp \
    libcore/Operator.cpp \
    libcore/Permissions.cpp \
    libcore/DefaultsFilePath.cpp \
    libcore/SettingsManager.cpp \
    guiModels/HeaderModel.cpp \
    Perm.cpp \
    guiModels/DocumentProtocol.cpp \
    CAManager.cpp \
    libJournal/Journal.cpp \
    libJournal/JournalFile.cpp \
    libJournal/JournalStorage.cpp \
    libJournal/JournalSyslog.cpp \
    libcore/LogsIO.cpp \
    guiModels/SessionReport.cpp \
    controller/connector/SerialPort.cpp \
    controller/connector/IODevWrapper.cpp \
    controller/connector/SerialPortWrapper.cpp \
    controller/connector/WiFiWrapper.cpp \
    controller/Connection.cpp \
    controller/connector/IOAVR.cpp \
    controller/connector/BluetoothWrapper.cpp

HEADERS += libcore/SettingsManager.h \
    libcore/DefaultsFilePath.h \
    guiModels/OperatorModel.h \
    libcore/Operator.h \
    libcore/Permissions.h \
    libcore/SettingsManager.h \
    libcore/Types.h \
    guiModels/HeaderModel.h \
    Perm.h \
    guiModels/DocumentProtocol.h \
    CAManager.h \
    libJournal/Journal.h \
    libJournal/JournalFile.h \
    libJournal/JournalStorage.h \
    libJournal/JournalSyslog.h \
    libcore/LogsIO.h \
    controller/ICommand.h \
    guiModels/SessionReport.h \
    controller/connector/SerialPort.h \
    controller/connector/IODevWrapper.h \
    controller/connector/SerialPortWrapper.h \
    controller/connector/WiFiWrapper.h \
    controller/Connection.h \
    controller/connector/IOAVR.h \
    controller/connector/BluetoothWrapper.h

HEADERS += \
    controller/DatabaseManager.h \
    controller/Autorization.h \
    controller/SettingsController.h \
    controller/EngineController.h

DISTFILES += \
    BaseElements/Numpad.qml \
    LedController.qml \
    main.qml \
    Settings.qml \
    Settings/AddUser.qml \
    BaseElements/BaseButton.qml \
    BaseElements/Constants.qml \
    BaseElements/BasePage.qml \
    ControllerPage.qml \
    BaseElements/Clock.qml \
    BaseElements/MenuButton.qml \
    BaseElements/WorkStatus.qml \
    BaseElements/StatusLight.qml \
    BaseElements/StartButton.qml \
    Autorization.qml \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    Settings/EnginesSettings.qml \
    DefaultSettings.qml \
    BaseElements/Notificator.qml \
    BaseElements/HeaderView.qml \
    android/src/org/RequestPermissions.java \
    Documents/DocProtocol.qml \
    BaseElements/BaseColumnComponent.qml \
    BaseElements/BaseTableView.qml \
    BaseElements/CertificateWarning.qml \
    Settings/LogsIO.qml \
    Settings/WiFiSettings.qml \
    BaseElements/LogOut.qml


include (android-openssl.pri)
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
