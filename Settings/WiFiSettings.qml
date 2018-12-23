import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "../BaseElements" as BaseElements

Rectangle {
    signal hide()
    color: "#CF000000"
    MouseArea{
        anchors.fill: parent
    }

    Rectangle{
        id: settings
        anchors.centerIn: parent
        width: parent.width * 1.2
        height: parent.width * 0.9
        color: "white"
        radius: 5

        GridLayout{
            id: settingsLayout
            width: settings.width * 0.95
            height: settings.height * 0.5
            anchors.topMargin: parent.height * 0.03
            anchors.left: parent.left
            anchors.leftMargin: parent.height * 0.03
            rows: 3
            columns: 2

            Text{
                text: qsTr("Enabled")
                color: constant.grey
                font.family: fontRoboto.name;
                font.pixelSize: parent.height * 0.1
            }

            CheckBox{
                Layout.alignment: Qt.AlignRight
                checked: false
                //onClicked: {defaultSettings.enabledBaseEngine = checked}
            }

            Text{
                text: qsTr("IP-adress")
                color: constant.grey
                font.family: fontRoboto.name;
                font.pixelSize: parent.height * 0.1
            }

            TextField{
                Layout.alignment: Qt.AlignRight
                text: "192.164.1.2"
            }

            Text{
                text: qsTr("Port")
                color: constant.grey
                font.family: fontRoboto.name;
                font.pixelSize: parent.height * 0.1
            }

            TextField{
                Layout.alignment: Qt.AlignRight
                text: "1929"
            }
        }

        BaseElements.BaseButton{
            id: save
            color: constant.green
            height: parent.height * 0.15
            anchors.bottom:  settings.bottom
            anchors.right: settings.right
            anchors.left: settings.left
            image: imagePath("Ok.png")
            hImageAlign: Image.AlignHCenter
            onClicked: {hide()}
        }
    }
}
