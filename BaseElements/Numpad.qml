/***************************************************************************
 *   Project name: *********                                               *
 *                                                                         *
 *   Copyright (C) 2018                                                    *
 *                                                                         *
 *   Authors:                                                              *
 *                                                                         *
 *   Dmitry Tereshchenko                                                         *
 *                  DmitryT@i.ua                               *
 *                  whois: YP977-UANIC                                     *
 *                                                                         *
 ***************************************************************************/


import QtQuick 2.0
import QtQuick.Window 2.0
import QtQuick.Controls 2.0

Rectangle
{
    property real numpadWidth: 0
    property real numpadHeight: 0
    property real index: 1

    signal addChar(var symbol)

    id: numpad
    color: "transparent"
    width: numpadWidth
    height: numpadHeight


    Grid{
        id: numpadGrid
        columns: 3
        rows: 3

        spacing: width * 0.06
        anchors.fill: parent

        Repeater {
            model: 9
            delegate: Rectangle{
                id: digit
                width: height
                height: d.buttonHeight
                radius: width * 0.5
                color: "transparent"
                border.color: "#40E0D0"
                border.width: 2
                Rectangle{
                    anchors.centerIn: parent
                    width: height
                    height: parent.height * 0.9
                    radius: width * 0.5
                    color: "transparent"

                    Text{
                        id: number
                        anchors.centerIn: parent
                        text: index + 1
                        font.bold: true
                        color: "#40E0D0"
                        font.pixelSize: parent.height * 0.5
                    }

                    MouseArea{
                        anchors.fill: parent
                        onPressed: {
                            number.color = "white"
                            digit.color = "#40E0D0"
                            addChar(number.text)
                        }
                        onReleased: {
                            number.color = "#40E0D0"
                            digit.color = "transparent"
                    }
                    }
                }
            }
        }
    }
    QtObject{
        id: d
        property real buttonHeight: (numpadGrid.height - (numpadGrid.spacing * (numpadGrid.rows - 1))) / numpadGrid.rows
        property real buttonWidth: (numpadGrid.width - (numpadGrid.spacing * (numpadGrid.columns - 1))) / numpadGrid.columns
    }
}
