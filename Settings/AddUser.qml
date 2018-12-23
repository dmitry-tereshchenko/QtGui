import QtQuick 2.0
import QtQuick.Controls 2.0
import "../BaseElements" as BaseElements

Rectangle {
    signal hide()
    property string phone: ""

    color: "#CF000000"

    MouseArea{
        anchors.fill: parent
    }

    Rectangle{
        anchors.centerIn: parent
        width: parent.width * 0.8
        height: width
        color: "white"
        radius: 5

        Connections{
            target: settingsController
            onAcceptNewUser: hide()
            onRejectNewUser: error.visible = true
        }

        BaseElements.BaseButton{
            id: save
            color: constant.green
            enabled: nameInput.length > 0 && passwordInput.length === passwordLength ? true : false
            height: parent.height * 0.15
            anchors.bottom:  parent.bottom
            anchors.bottomMargin: parent.height * 0.02
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.05
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.52

            image: imagePath("Ok.png")
            hImageAlign: Image.AlignHCenter
            onClicked: {
                phone = phoneInput.text.replace(/[\D]/g, '')
                settingsController.addNewUser(nameInput.text, passwordInput.text, phone, permissions.currentIndex + 1)
            }
        }

        BaseElements.BaseButton{
            id: cancel
            color: constant.red
            height: parent.height * 0.15
            anchors.right: parent.right
            anchors.rightMargin: parent.width * 0.52
            anchors.bottom:  parent.bottom
            anchors.bottomMargin: parent.height * 0.02
            anchors.left: parent.left
            anchors.leftMargin: parent.width * 0.05

            image: imagePath("Cancel.png")
            hImageAlign: Image.AlignHCenter
            onClicked: {hide()}
        }

        Column {
            id: column
            spacing: 10
            anchors{
                top: parent.top
                topMargin: parent.height * 0.05
                bottom: cancel.top
                bottomMargin: parent.height * 0.05
                left: parent.left
                leftMargin: parent.width * 0.05
                right: parent.right
                rightMargin: parent.width * 0.05
            }
            Column{
                Text {
                    text: "*" + qsTr("Name")
                    font.pixelSize: column.height * 0.05
                    color: constant.red
                }

                TextField {
                    id: nameInput
                    selectByMouse: false
                    width: column.width
                    height: column.height * 0.15
                    font.pixelSize: column.height * 0.07
                }
            }

            Column{
                Text {
                    text: "*" + qsTr("Level")
                    font.pixelSize: column.height * 0.05
                    color: constant.red
                }

                ComboBox {
                    id: permissions
                    editable: false
                    width: column.width
                    displayText: currentText
                    height: column.height * 0.15
                    font.pixelSize: column.height * 0.05
                    model: operatorModel
                    onAccepted: {
                        if (find(editText) === -1)
                            model.append({text: editText})
                    }
                }
            }

            Column{
                Text {
                    text: "*" + qsTr("Password")
                    font.pixelSize: column.height * 0.05
                    color: constant.red
                }

                TextField {
                    id: passwordInput
                    selectByMouse: false
                    echoMode: TextInput.Password
                    width: column.width
                    height: column.height * 0.15
                    font.pixelSize: column.height * 0.07
                    validator: IntValidator{bottom: 0; top: {
                            var topLevel = '9'
                            for(var it = 0; it < passwordLength-1; it++)
                                topLevel += '9'
                           return topLevel
                        }
                    }
                }

                Text {
                    id: error
                    text: qsTr("Wrong password!")
                    color: constant.red
                    visible: false
                    font.bold: true
                    font.pixelSize: column.height * 0.05
                }
            }

            Column{
                Text {
                    text: qsTr("Phone number")
                    font.pixelSize: column.height * 0.05
                    color: constant.grey
                }

                TextField {
                    id: phoneInput
                    enabled: isEnabledPhone
                    selectByMouse: false
                    height: column.height * 0.15
                    width: column.width
                    inputMask: countryCode + phoneMask
                    font.pixelSize: column.height * 0.07
                    cursorPosition: 1
                }
            }
        }
    }
}
