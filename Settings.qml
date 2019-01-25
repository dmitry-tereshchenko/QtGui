import QtQuick 2.0
import QtQuick.Layouts 1.3

import "Settings" as Settings
import "BaseElements" as BaseElements
import CreateOptics 1.0

Rectangle {
    signal hide()
    color: "#CF000000"
    MouseArea{
        anchors.fill: parent
    }

    Rectangle{
        anchors.centerIn: parent
        width: arWidth(parent.width * 0.5)
        height: parent.height

        Item{
            id: pageSettings
            anchors{
                fill: parent
                rightMargin: parent.width * 0.02
                leftMargin: parent.width * 0.02
                topMargin: parent.width * 0.02
                bottomMargin: parent.height * 0.1
            }
            ColumnLayout{
                anchors.fill: parent
                spacing: parent.height * 0.05
                Text{
                    id: newUser
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: constant.blue
                    font.pixelSize: parent.width * 0.05
                    font.underline: true
                    text: qsTr("Add new user")
                    font.italic: true
                    font.bold: true
                    MouseArea{
                        anchors.fill: parent
                        onClicked: permissions.isPermissions(Permissions.ADD_NEW_USER) ? loaderNewUser.sourceComponent = newUserComponent : popupLoader.sourceComponent = notificator
                    }
                }

                Text{
                    id: enginesSettings
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: constant.blue
                    font.pixelSize: parent.width * 0.08
                    text: qsTr("Engines settings")
                    font.bold: true
                    MouseArea{
                        anchors.fill: parent
                        onClicked: loaderNewUser.sourceComponent = enginesSett
                    }
                }

                Text{
                    id: logs
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: constant.blue
                    font.pixelSize: parent.width * 0.08
                    text: qsTr("Logs")
                    font.bold: true
                    MouseArea{
                        anchors.fill: parent
                        onClicked: loaderNewUser.sourceComponent = logsio
                    }
                }

                Text{
                    id: wifiSettings
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    color: constant.blue
                    font.pixelSize: parent.width * 0.08
                    text: qsTr("Connect")
                    font.bold: true
                    MouseArea{
                        anchors.fill: parent
                        onClicked: loaderNewUser.sourceComponent = wifi
                    }
                }
            }
        }

        BaseElements.BaseButton{
            id: save
            color: constant.green
            anchors{
                bottom:  parent.bottom
                top: pageSettings.bottom
                left: pageSettings.left
                right: pageSettings.right
                leftMargin: parent.width * 0.5
            }
            image: imagePath("Ok.png")
            hImageAlign: Image.AlignHCenter
            onClicked: hide()
        }

        BaseElements.BaseButton{
            id: cancel
            color: constant.red
            height: parent.height * 0.1
            anchors{
                bottom:  parent.bottom
                top: pageSettings.bottom
                left: pageSettings.left
                right: pageSettings.right
                rightMargin: parent.width * 0.5
            }

            image: imagePath("Cancel.png")
            hImageAlign: Image.AlignHCenter
            onClicked: hide()
        }

        Loader{
            id: loaderNewUser
            anchors.fill: parent
            sourceComponent: undefined
        }

        Component{
            id: newUserComponent
            Settings.AddUser{
                onHide: loaderNewUser.sourceComponent = undefined
            }
        }

        Component{
            id: enginesSett
            Settings.EnginesSettings{
                onHide: loaderNewUser.sourceComponent = undefined
            }
        }

        Component{
            id: logsio
            Settings.LogsIO{
                onHide: loaderNewUser.sourceComponent = undefined
            }
        }

        Component{
            id: wifi
            Settings.WiFiSettings{
                onHide: loaderNewUser.sourceComponent = undefined
            }
        }
    }
}
