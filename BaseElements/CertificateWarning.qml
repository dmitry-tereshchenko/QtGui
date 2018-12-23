import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.3
import QtQuick.Layouts 1.3
import CreateOptics 1.0
import QtQuick.Controls.Styles 1.4

Rectangle {
    signal accept()

    Component.onCompleted: startAnim.start()
    CAManager{id: manager}

    id: notificator
    color: "#CF000000"
    MouseArea{
        anchors.fill: parent
    }

    Rectangle{
        id: notificatorWindow
        anchors.horizontalCenter: parent.horizontalCenter
        width: arWidth(parent.width * 0.5)
        height: width * 0.75
        color: "white"

        ColumnLayout{
            width: parent.width * 0.95
            height: parent.height * 0.9
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: constant.hSpacing

            Text{
                Layout.fillWidth: true
                text: qsTr("License expired") + "!" + " " + qsTr("Please add a new license")
                font.pixelSize: constant.sTextSize
                wrapMode: Text.WordWrap
                horizontalAlignment: Text.AlignHCenter
                maximumLineCount: 4
                color: constant.grey
            }

            Text{
                id: status
                Layout.fillWidth: true
                font.weight: Font.Bold
                font.pixelSize: constant.mTextSize
                horizontalAlignment: Text.AlignHCenter
                opacity: 0
            }

            Item{
                width: parent.width - imageTexField.width - (parent.width * 0.05)
                height: parent.height * 0.15
                TextField{
                    id: numberField
                    width: parent.width
                    height: parent.height
                    textColor: constant.grey
                    anchors.top: imageTexField.top
                    font.pixelSize: constant.sTextSize
                    enabled: false
                    style: TextFieldStyle{
                        background: Rectangle {
                            border.color: constant.blue
                            border.width: 1
                        }
                    }
                }

                Rectangle{
                    id: imageTexField
                    anchors.left: numberField.right
                    height: parent.height
                    width: height
                    Image {
                        source: imagePath("add.png")
                        anchors.centerIn: parent
                        sourceSize.height: parent.height * 0.6
                    }
                    MouseArea{
                        anchors.fill: parent
                        onPressed: {parent.color = constant.lightgrey}
                        onReleased: {parent.color = "white"; dialog.open()}
                    }
                }
            }

            BaseButton{
                id: confirmButton
                Layout.fillWidth: true
                height: parent.height * 0.15
                text: qsTr("read key")
                enabled: false
                textSize: constant.sTextSize
                color: constant.green
                radius: 0
                onClicked: {
                    if(manager.isReadNewCertificate(numberField.text)){
                        status.text = "Ok"
                        status.color = constant.green
                    }
                    else{
                        status.text = "Failed"
                        status.color = constant.red
                    }
                    status.opacity = 1
                }
            }

            Item {
                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }

        FileDialog{
            id: dialog
            folder: shortcuts.home
            onAccepted: {
                var path = dialog.fileUrl.toString()
                numberField.text = path.replace("file://","")
                confirmButton.enabled = true
            }
        }

        BaseButton{
            anchors.bottom: parent.bottom
            width: parent.width
            height: parent.height * 0.15
            text: qsTr("close application")
            textSize: constant.sTextSize
            color: constant.red
            radius: 0
            onClicked: accept()
        }
    }

    PropertyAnimation {
        id: startAnim
        target: notificatorWindow
        property: "y"
        from: notificatorWindow.y
        to: Screen.height / 2 - (notificatorWindow.height / 2)
        easing.type: Easing.InOutQuad; duration: 200
    }
}
