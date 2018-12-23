import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "../BaseElements" as BaseElements
import CreateOptics 1.0
Rectangle {
    signal hide()
    color: "#CF000000"
    Component.onCompleted: {logText.text = fileIO.read()}
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
            anchors.leftMargin: parent.width * 0.03
            anchors.rightMargin: parent.width * 0.03
            contentHeight: logText.height
            contentWidth: logText.width
            boundsBehavior: Flickable.DragAndOvershootBounds
            ScrollBar.vertical: ScrollBar {}
            clip: true
            onMovingChanged: {animateOpacity.start(); timeEnable.start()}

            Text {
                id: logText
                font.pixelSize: constant.sTextSize * 0.8
                font.family: fontRoboto.name;
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
        LogsIO{
            id: fileIO
            source: logPath
        }
    }
}
