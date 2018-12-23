import QtQuick 2.0
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.4
import QtQml 2.2
import CreateOptics 1.0

import "BaseElements" as BaseElements

Rectangle{
    Account {id: account}
    CAManager{id: managerCert}
    Component.onCompleted: {
        if(!managerCert.isValidCertificate())
            loader.sourceComponent = certError
    }

    signal error()
    signal success()
    color: "#FFFFF0"

    TextField{
        id: login
        anchors{
            left: numpad.left
            right: numpad.right
            bottom: numpad.top
            bottomMargin: height
        }
        readOnly: true
        selectByMouse: false
        height: numpad.height/6
        echoMode: TextInput.Password
        textColor: "#40E0D0"
        horizontalAlignment: TextInput.AlignHCenter
        style: TextFieldStyle {
            background: Rectangle { color: "transparent" }
        }

        Rectangle{
            width: parent.width
            height: 2
            color: "#40E0D0"
            anchors.top: parent.bottom
        }
    }

    BaseElements.Numpad{
        id: numpad
        anchors.horizontalCenter: parent.horizontalCenter
        anchors{
            bottom: parent.bottom
            bottomMargin: parent.height * 0.1
        }

        width: arWidth(parent.width) * 0.8
        height: width

        onAddChar: {
            login.text += symbol
            //loginfunc(login.text)
            if(login.length > passwordLength)
                login.text = ""
        }
    }

    Rectangle {
        id: datetime
        anchors.top: numpad.top
        anchors.bottom: numpad.bottom
        anchors.left: numpad.right
        anchors.leftMargin: parent.width * 0.05
        radius: width * 0.2
       // horizontalAlignment: Text.AlignHCenter
        width: numpad.width * 0.2
        border.width: 2
        border.color: "#40E0D0"
        color: "transparent"
        Image {
            source: imagePath("right-arrow.png")
            anchors.centerIn: parent
            height: parent.width * 0.8
            width: parent.width * 0.8

        }
        MouseArea{
            anchors.fill: parent
            onPressed: parent.color = "white"
            onReleased: {parent.color = "transparent"; loginfunc(login.text)}
        }

        //text:  Qt.formatDateTime(new Date(), "ddd yyyy/MM/dd hh:mm")
    }

    function loginfunc(m_login)
    {
        if(m_login.length === passwordLength){
            if(account.login(m_login)){
                success()
                login.text = ""
            }
            else
                login.text = ""
        }
    }
    Loader {id: loader; anchors.fill: parent; sourceComponent: undefined}
    Component {id: certError; BaseElements.CertificateWarning{onAccept: Qt.quit()}}
}

