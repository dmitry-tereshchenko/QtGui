import QtQuick 2.2
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Rectangle{
    id: light
    property real size: 20
    property bool glow: true
    property real sizeBorder: size * 0.05

    radius: size
    height: size
    width: height
    border.color: "#15000000"
    border.width: sizeBorder
    Loader{
        id: disableLoader
        anchors.fill: parent
        sourceComponent: glow ? undefined : disableComponent
    }
    Component{
        id: disableComponent
        Rectangle{
            radius: size
            height: size
            width: height
            color: "#A0FFFFFF"
        }
    }
    layer.enabled: glow
    layer.effect: Glow {
        samples: radius * 3
        radius: light.height * 0.7
        color: light.color
        transparentBorder: true
        spread: 0.3
    }
}
