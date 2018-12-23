import QtQuick 2.0

Item {
    property string role : ""
    property string title : ""
    property real columnSpan : 1
    property int horizontalAlign: Text.AlignLeft
    property bool locateField: false
    property Component delegate
}
