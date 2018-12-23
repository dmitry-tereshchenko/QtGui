/***************************************************************************
 *   Project name: Chameleon                                               *
 *                                                                         *
 *   Copyright (C) 2008                                                    *
 *                                                                         *
 *   Authors:                                                              *
 *                                                                         *
 *   Yuriy Poltorak                                                        *
 *                  yuriy.poltorak@gmail.com                               *
 *                  whois: YP977-UANIC                                     *
 *                                                                         *
 ***************************************************************************/


import QtQuick 2.0

Item
{
    id: lightButton
    property string text
    property string image
    property color textColor: "white"
    property color color: constant.green
    property real radius: height * 0.05
    property color disabledColor: constant.lightgrey
    property real textSize: width * 0.5
    property real imageSize: height * 0.65
    property real hSpacing: constant.hSpacing
    property real vSpacing: constant.vSpacing
    property int hTextAlign: Text.AlignLeft
    property int hImageAlign: Image.AlignRight
    property int fontWeight: Font.Bold
    property bool shadow: false

    property real effectWidth: lightButton.width * 0.005
    signal clicked()
    signal pressed()
    signal released()

    Rectangle{
        anchors.fill: parent
        color: enabled ? lightButton.color : disabledColor
        radius: lightButton.radius
        Loader{
            id: topBorderLoader
            height: parent.height* 0.03
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
                leftMargin: effectWidth
                rightMargin: effectWidth
            }
            sourceComponent: shadow ? topBorder : undefined
        }
        Component{
            id: topBorder
            Rectangle{
                anchors.fill: parent
                radius: lightButton.radius
                color: "white"
                opacity: 0.3
            }
        }
        Loader{
            id: bottomBorderLoader
            height: parent.height* 0.05
            anchors{
                bottom: parent.bottom
                left: parent.left
                right: parent.right
                leftMargin: effectWidth
                rightMargin: effectWidth
            }
            sourceComponent: shadow ? bottomBorder : undefined
        }
        Component{
            id: bottomBorder
            Rectangle{
                radius: lightButton.radius
                color: "black"
                opacity: 0.2
            }
        }

        Loader{id: overlayLoader; anchors.fill: parent}
        Component{id: overlayArea; Rectangle{anchors.fill: parent; radius: lightButton.radius; color: "black"; opacity: 0.4}}

        Loader{id: dataLoader; anchors{fill: parent;leftMargin: hSpacing; rightMargin: hSpacing; topMargin: vSpacing; bottomMargin: vSpacing} sourceComponent: d.getComponent()}
        Component{
            id: comboComponent
            Item{
                anchors.fill: parent
                Text {
                    height: parent.height
                    width: parent.width - imageRow.width
                    text: lightButton.text
                    color: textColor
                    font.pixelSize: textSize
                    font.capitalization: Font.AllUppercase
                    font.weight: fontWeight
                    maximumLineCount: 3
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: hTextAlign
                }
                Image{
                    ///verticalAlignment and horizontalAlignment doesn't work
                    id: imageRow
                    sourceSize.height: lightButton.imageSize
                    source: lightButton.image
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: hImageAlign === Image.AlignLeft ? parent.left : undefined
                        right: hImageAlign === Image.AlignRight ? parent.right : undefined
                        centerIn: hImageAlign === Image.AlignHCenter ? parent : undefined
                    }
                }
            }
        }

        Component{
            id: imageComponent
            Item{
                anchors.fill: parent
                Image{
                    sourceSize.height: lightButton.imageSize
                    source: lightButton.image
                    anchors{
                        verticalCenter: parent.verticalCenter
                        left: hImageAlign === Image.AlignLeft ? parent.left : undefined
                        right: hImageAlign === Image.AlignRight ? parent.right : undefined
                        centerIn: hImageAlign === Image.AlignHCenter ? parent : undefined
                    }
                }
            }
        }
        Component{
            id: textComponent
            Text {
                anchors.fill: parent
                text: lightButton.text
                color: textColor
                font.pixelSize: textSize
                font.capitalization: Font.AllUppercase
                font.weight: fontWeight
                maximumLineCount: 2
                wrapMode: Text.WordWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: hTextAlign
            }
        }

        MouseArea{
            anchors.fill: parent
            enabled: lightButton.enabled
            onPressed: {overlayLoader.sourceComponent = overlayArea; radius = lightButton.radius * 1.3; lightButton.pressed()}
            onReleased: {overlayLoader.sourceComponent = undefined; radius = lightButton.radius / 1.3; lightButton.released()}
            onClicked: { lightButton.clicked()}
        }

        QtObject{
            id: d
            function getComponent()
            {
                /// кнопка с текстом и картинкой
                if(lightButton.image.length && lightButton.text.length)
                    return comboComponent
                if(lightButton.image.length)
                    return imageComponent
                if(lightButton.text.length)
                    return textComponent
                return undefined
            }
        }
    }
}
