import QtQuick 2.0

Rectangle{
    signal logOut()
    signal exit()

    color: "#090F25"

    Rectangle{
        id: centerBttn
        anchors.centerIn: parent
        width: parent.height * 0.3
        height: parent.height * 0.3
        color: "#46A1F7"
        Text {
            width: parent.width * 0.9
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            text: qsTr("Log Out")
            font.pixelSize: constant.sTextSize * 0.8
        }
        Image {
            anchors{
                top: parent.top
                left: parent.left
                leftMargin: parent.width * 0.07
                topMargin: parent.width * 0.07
            }

            width: parent.width * 0.25
            height: width
            source: imagePath("user.png")
        }
        MouseArea{anchors.fill: parent; onClicked: {logOut()}}
    }

    Rectangle{
        id: leftBttn
        anchors.top: centerBttn.top
        anchors.right: centerBttn.left
        anchors.rightMargin: parent.width * 0.008
        width: parent.height * 0.3
        height: parent.height * 0.3
        color: "#3265E5"
    }

    Rectangle{
        id: rightBttn
        anchors.top: centerBttn.top
        anchors.left: centerBttn.right
        anchors.leftMargin: parent.width * 0.008
        width: parent.height * 0.3
        height: parent.height * 0.3
        color: "#169563"
        Text {
            width: parent.width * 0.9
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            text: qsTr("Exit")
            font.pixelSize: constant.sTextSize * 0.8
        }
        Image {
            anchors{
                top: parent.top
                left: parent.left
                leftMargin: parent.width * 0.07
                topMargin: parent.width * 0.07
            }

            width: parent.width * 0.25
            height: width
            source: imagePath("error.png")
        }
        MouseArea{anchors.fill: parent; onClicked: {exit()}}
    }
}
