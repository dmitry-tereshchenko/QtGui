/***************************************************************************
 *   Project name: Laguna                                                  *
 *                                                                         *
 *   Copyright (C) 2018                                                    *
 *                                                                         *
 *   Authors:                                                              *
 *                                                                         *
 *   Dmitry Tereshchenko                                                   *
 *                  DmitryT@i.ua                                           *
 *                  whois: YP977-UANIC                                     *
 *                                                                         *
 ***************************************************************************/


import QtQuick 2.0

Item{
    id: basePage

    /// Данные для базовой страницы
    property alias centerData: centerItem.data
    property alias headerData: headerItem.data
    property alias sliceData: sliceItem.data

    /// Настройка пропорций базoвой страницы
    property real centrItemWidth: width * 0.5
    property real headerHeight: (height * 0.03) * 2.5
    property real leftDataWidth: width * 0.2
    property real windowsHeight: height
    property real windowsWidth: width
    property bool isVisibleBorder: true
    MouseArea{anchors.fill: parent}         /// перехватываем нажатия, чтоб не проходили сквозь страницу

    Item {
        id: body
        anchors{
            top: parent.top
            topMargin: parent.height * 0.1
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        Item{
            id: headerItem
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
            }
            height: headerHeight
        }


        Item{
            id: centerItem
            anchors{
                top: headerItem.bottom
                bottom: parent.bottom
                right: parent.right
                left: sliceItem.right
            }
        }

        Item{
            id: sliceItem
            height: parent.height
            width: leftDataWidth
            anchors{
                top: centerItem.top
                bottom: centerItem.bottom
            }

            Rectangle{
                anchors{
                    right: parent.right
                    top: parent.top
                    bottom: parent.bottom
                }
                visible: isVisibleBorder
                color: constant.grey
                width: 1
            }
        }
    }
}
