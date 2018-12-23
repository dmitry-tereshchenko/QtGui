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

Item {
    property string grey: "#434343"
    property string green: "#69bc6a"
    property string blue: "#00adf1"
    property string red: "#ea5858"
    property string lightred: "#db7d7d"
    property string lightgreen: "#bdeebe"
    property string lightgrey: "#bcbcbc"
    property string mediumgrey: "#989898"
    property string yellow: "#caa946"
    property string lightyellow: "#e7c04e"
    property string noActiveGreen: "#e0ebdd"
    property string noActiveRed: "#f2dadb"
    property string noActiveBorderGreen: "#f2dadb"

    readonly property real buttonHeight: height * 0.15
    readonly property real buttonWidh: width * 0.35

    readonly property real hSpacing: width * 0.03
    readonly property real vSpacing: height * 0.01
    readonly property real lTextSize: height * 0.08
    readonly property real mTextSize: height * 0.05
    readonly property real sTextSize: height * 0.04
    readonly property real lButtonTextSize: height * 0.04
    readonly property real mButtonTextSize: height * 0.03
    readonly property real sButtonTextSize: height * 0.02

}
