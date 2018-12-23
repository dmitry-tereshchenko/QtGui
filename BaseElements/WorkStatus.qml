import QtQuick 2.0

ListView{
    id: lightsView
    orientation: ListView.Horizontal
    interactive: false
    model: ListModel{
        id: lightsModel
        ListElement {color: "#ea5858"}
        ListElement {color: "#caa946"}
        ListElement {color: "#69bc6a"}
    }
    delegate: Item{
        width: lightsView.width / lightsView.count
        height: parent.height
        property bool isCurrent: ListView.isCurrentItem ? true : false
        Loader{
            id: delegateLoader
            anchors.centerIn: parent
            width: parent.height * 0.6
            height: width
            sourceComponent: isCurrent ? enabledLight : disabledLight
            Component{
                id: enabledLight
                StatusLight{
                    size: delegateLoader.height
                    glow: true
                    color: model.color
                }
            }
            Component{
                id: disabledLight
                StatusLight{
                    size: delegateLoader.height
                    glow: false
                    color: model.color
                }
            }
        }
    }
}

