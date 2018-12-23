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

        Flickable{
            anchors.fill: parent
            contentHeight: settingsLayout.height * 3
            contentWidth: settingsLayout.width
            boundsBehavior: Flickable.StopAtBounds
            ScrollBar.vertical: ScrollBar {}
            clip: true
            onMovingChanged: {animateOpacity.start(); timeEnable.start()}

            Text {
                id: settingsBaseEng
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: parent.height * 0.03
                font.pixelSize: parent.height * 0.04
                font.bold: true
                color: constant.red
                font.family: fontRoboto.name;
                text: qsTr("Settings base engine")
            }

            GridLayout{
                id: settingsLayout
                width: settings.width * 0.95
                height: settings.height * 0.5
                anchors.top: settingsBaseEng.bottom
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
                    checked: defaultSettings.enabledBaseEngine
                    onClicked: {defaultSettings.enabledBaseEngine = checked}
                }

                Text{
                    text: qsTr("Rate of change in speed")
                    color: constant.grey
                    font.family: fontRoboto.name;
                    font.pixelSize: parent.height * 0.1
                }

                SpinBox{
                    implicitHeight: parent.height * 0.2
                    font.pixelSize: parent.height * 0.12
                    Layout.alignment: Qt.AlignRight
                    value: defaultSettings.stepBaseEngineCount
                    onValueChanged: {defaultSettings.stepBaseEngineCount = value}
                }

                Text{
                    text: qsTr("Max. speed")
                    color: constant.grey
                    font.family: fontRoboto.name;
                    font.pixelSize: parent.height * 0.1
                }

                SpinBox{
                    font.pixelSize: parent.height * 0.12
                    implicitHeight: parent.height * 0.2
                    Layout.alignment: Qt.AlignRight
                    value: defaultSettings.rotateBaseEngineCount
                    onValueChanged: {defaultSettings.rotateBaseEngineCount = value}
                }
            }

            Text {
                id: settingsSecondEng
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: settingsLayout.bottom
                font.pixelSize: parent.height * 0.04
                font.bold: true
                color: constant.red
                font.family: fontRoboto.name;
                text: qsTr("Settings secondary engine")
            }

            GridLayout{
                id: settingsLayout2
                width: settings.width * 0.95
                height: settings.height * 0.5
                anchors.top: settingsSecondEng.bottom
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
                    checked: defaultSettings.enabledSecondaryEngine
                    onClicked: {defaultSettings.enabledSecondaryEngine = checked}
                }

                Text{
                    text: qsTr("Rate of change in speed")
                    color: constant.grey
                    font.family: fontRoboto.name;
                    font.pixelSize: parent.height * 0.1
                }

                SpinBox{
                    font.pixelSize: parent.height * 0.12
                    implicitHeight: parent.height * 0.2
                    Layout.alignment: Qt.AlignRight
                    value: defaultSettings.stepSecondaryEngineCount
                    onValueChanged: {defaultSettings.stepSecondaryEngineCount = value}
                }

                Text{
                    text: qsTr("Max. speed")
                    color: constant.grey
                    font.family: fontRoboto.name;
                    font.pixelSize: parent.height * 0.1
                }

                SpinBox{
                    font.pixelSize: parent.height * 0.12
                    implicitHeight: parent.height * 0.2
                    Layout.alignment: Qt.AlignRight
                    value: defaultSettings.rotateSecondaryEngineCount
                    onValueChanged: {defaultSettings.rotateSecondaryEngineCount = value}
                }
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
            enabled: opacity === 0.0 ? false : true
            opacity: 0.0

        }

        NumberAnimation {
            id: animateOpacity
            target: save
            properties: "opacity"
            from: 0.0
            to: 1.0
            easing {type: Easing.OutBack}
            duration: 800
       }

        NumberAnimation {
            id: animateOpacit
            target: save
            properties: "opacity"
            from: 1.0
            to: 0.0
            easing {type: Easing.OutBack}
            duration: 800
       }

        Timer{
            id: timeEnable
            interval: 2000
            running: false
            repeat: false
            onTriggered:{animateOpacit.start()}
        }
    }
}
