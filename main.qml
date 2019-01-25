import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
import CreateOptics 1.0
import "BaseElements" as BaseElements
import "Documents" as Documents

ApplicationWindow {
    id: applicationWindow
    visible: true
    title: qsTr("LedControl")
    color: "white"
    //width: 800
    //height: 500
    modality: Qt.ApplicationModal
    Component.onCompleted: applicationWindow.showFullScreen()

    SettingsController {id: settingsController}
    BaseElements.Constants{id: constant; anchors.fill: parent}
    OperatorModel{id: operatorModel}
    HeaderModel {id: headerModel}
    DefaultSettings{id: defaultSettings}

    Component{
        id: notificator
        BaseElements.Notificator{
            messageError: qsTr("No Permissions")
        }
    }

    SwipeView{
        id: swipeView
        currentIndex: 0
        interactive: false
        anchors.fill: parent
        Autorization{onSuccess: {swipeView.incrementCurrentIndex(); d.resizeHeader(0)}}
        ControllerPage{}
        Documents.DocProtocol{id: docProtocol}
        BaseElements.BasePage{isVisibleBorder: false; leftDataWidth: 0; centerData: Text {
                anchors.centerIn: parent
                text: qsTr("Страница в разработке")
                font.bold: true
                color: constant.red
            }}
        BaseElements.BasePage{isVisibleBorder: false; leftDataWidth: 0; centerData: Text {
                anchors.centerIn: parent
                text: qsTr("Страница в разработке")
                font.bold: true
                color: constant.red
            }}
        BaseElements.BasePage{isVisibleBorder: false; leftDataWidth: 0; centerData: Text {
                anchors.centerIn: parent
                text: qsTr("Страница в разработке")
                font.bold: true
                color: constant.red
            }}
    }

    BaseElements.HeaderView{
        id: headerView
        anchors{
            left: parent.left
            right: parent.right
        }
        height: parent.height * 0.1
        y: -height
        onClick: {
            switch(index){
            case HeaderModel.SETTINGS: settingsLoader.sourceComponent = settings; break;
            case HeaderModel.MENU: settingsLoader.sourceComponent = lol; break;
            default: swipeView.currentIndex = index; break;
            }
        }
    }

    Loader{
        id: settingsLoader
        anchors.fill: parent
        sourceComponent: undefined
    }

    Component{
        id: settings
        Settings{
            onHide: settingsLoader.sourceComponent = undefined
        }
    }

    Component{
        id: lol
        BaseElements.LogOut{
            onExit: Qt.quit()
            onLogOut: {
                swipeView.currentIndex = 0
                d.resizeHeader(-headerView.height)
                settingsLoader.sourceComponent = undefined
            }
        }
    }

    FontLoader
    {
        id: fontRoboto;
        source: "qrc:/assets/font/Roboto-Regular.ttf";
    }

    function imagePath(imageName)
    {
        return 'qrc:/assets/images/' + imageName;
    }

    function arWidth(width)
    {
        if(d.aspectRatio > 1.33)    /// если не 4:3
            return height / d.aspectRatio * 1.33
        return width
    }

    /// Лоадер для диалоговых окон
    Loader{
        id: popupLoader
        anchors.fill: parent
        sourceComponent: undefined
    }
    QtObject{
        id: d
        property real aspectRatio: applicationWindow.width / applicationWindow.height
        function resizeHeader(m_y){
            headerView.y = m_y
        }
    }
}
