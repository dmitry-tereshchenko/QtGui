import QtQuick 2.0
import QtQuick.Window 2.3
import CreateOptics 1.0

Rectangle {
    property string messageError
    property int displayTime: 2 ///< Диалоговое окно висит 2 сек

    Component.onCompleted: startAnim.start()

    id: notificator
    color: "#CF000000"
    MouseArea{
        anchors.fill: parent
    }

    Timer{
        id: notificatorTime
        interval: displayTime * 1000
        onTriggered: {endAnim.start()}
    }

    Rectangle{
        id: notificatorWindow
        anchors.horizontalCenter: parent.horizontalCenter
        width: arWidth(parent.width * 0.5)
        y: -height
        height: width * 0.75
        color: "white"
        radius: parent.width * 0.03
        Item {
            height: parent.height
            width: parent.width * 0.9
            anchors.centerIn: parent

            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                maximumLineCount : 3
                wrapMode: Text.WordWrap
                text: qsTr(messageError)
                font.pixelSize: constant.sTextSize
                font.weight: Font.Bold
                color: constant.red
            }
        }
    }

    PropertyAnimation {
        id: startAnim
        target: notificatorWindow
        property: "y"
        from: notificatorWindow.y
        to: Screen.height / 2 - (notificatorWindow.height / 2)
        easing.type: Easing.InOutQuad; duration: 200
        onStopped: notificatorTime.start()
    }

    PropertyAnimation {
        id: endAnim
        target: notificatorWindow
        property: "y"
        from: notificatorWindow.y
        to: -notificatorWindow.height
        easing.type: Easing.InOutQuad
        duration: startAnim.duration
        onStopped: popupLoader.sourceComponent = undefined
    }
}
