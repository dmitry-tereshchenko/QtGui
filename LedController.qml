import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.0
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4

Item {
    id: item1

    Rectangle{
        id: connect
        color: "#99ffcc"
        width: parent.width
        height: parent.height/4
        Text{
            id: txt
            anchors.centerIn: parent
            text: "Connect"
        }
        Rectangle{
            color: "grey"
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            height: 1
        }

        MouseArea{
            anchors.fill: parent
            onClicked:{
                drawer.open()
                if(txt.text === "Connect" && led.connect()){
                    if(led.connect()){
                        txt.text = "Disconnect"
                        parent.color = '#ff3300'
                    }
                    else
                    {
                        txt.text = "Connect"
                        parent.color = '#99ffcc'
                    }
                }
                else if(txt.text === "Disconnect"){
                    if(led.disconnect()){
                        txt.text = "Connect"
                        parent.color = '#99ffcc'
                    }
                }
            }
        }
    }

    Rectangle{
        id: on
        color: txt.text === "Connect" ? "#FFFF66" : "#99ffcc"
        width: parent.width
        height: parent.height / 4
        anchors.top: connect.bottom
        Text{
            anchors.centerIn: parent
            text: "on"
        }

        Rectangle{
            color: "grey"
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            height: 1
        }

        MouseArea{
            anchors.fill: parent
            onClicked:{
                led.on()
            }
        }
    }

    Rectangle{
        id: off
        color: txt.text === "Connect" ? "#FFFF66" : "#99ffcc"
        width: parent.width
        height: parent.height / 4
        anchors.top: on.bottom

        Rectangle{
            color: "grey"
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            height: 1
        }

        Text{
            anchors.centerIn: parent
            text: "off"
        }

        MouseArea{
            anchors.fill: parent
            onClicked:{
                led.off()
            }
        }
    }

    Slider{
        id: control
        height: parent.height / 4
        to: 10.0
        from: 0.0
        stepSize: 1.0
        value: txt.text === "Connect" ? 0.0 : 0.0
        anchors.horizontalCenter: parent.horizontalCenter
        width: height
        anchors.top: off.bottom

        handle: Rectangle {
            anchors.verticalCenter: parent.verticalCenter
            width: parent.width * 0.2
            height: width
            radius: width * 0.5
            color: control.pressed ? "#33A0C1" : "#33A0C1"
            y: control.leftPadding + control.availableWidth / 2 - width / 2
            x: control.topPadding + control.visualPosition * (control.availableHeight - height)
            Text {
                anchors.centerIn: parent
                text: control.value
            }
        }

        //        Text{
        //            id: text
        //            anchors.centerIn: parent
        //            text: Math.round(parent.value)
        //            color: parent.value > (4/5) * parent.to ? "red" : "black"
        //        }
        onPositionChanged:{led.on(25.5 * value)}
        //enabled: txt.text === "Connect" ? false : true
    }
}
