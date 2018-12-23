import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

// Аналог TableView

Item {
    property alias m_model: dataList.model
    property int visibleRow: 6
    property real headerHeight: tableView.height / 10
    property bool hideScrollIndicator: false
    property bool block: false
    property bool isChessBackground: false
    property list<BaseColumnComponent> m_header

    property string headerTextColor: "#1D3546"
    property string columnTextColor: "#1D3546"
    property string rowBackgroundColor: "transparent"
    property string headerBackgroundColor: "white"
    property string highlightRowColor: "#302196F3"
    property real headerFontSize: 35 // В процентом соотношении относительно высоты ячейки
    property real columnFontSize: 25 // В процентом соотношении относительно высоты ячейки
    property bool headerFontBold: true
    property bool columnFontBold: false
    property bool isHeighlight: true
    property bool isLoading: false
    property real columnSpanCoef: 0.65
    readonly property var columnCount: m_header.length
    property alias currentIndex: dataList.currentIndex
    property alias headerPositioning: dataList.headerPositioning

    signal doubleClick(var index)
    signal click(var index)
    signal pressAndHold(var index)
    signal pressAndHoldRelise()

    id: tableView
    Component.onCompleted: d.initWidth(); onWidthChanged: d.initWidth(); onHeightChanged: d.initWidth()
    anchors.fill: parent

    property Component tableHeader: Rectangle {
        id: tableHeader
        width: d.rowWidth
        height: headerHeight
        color: headerBackgroundColor
        z: 1000
        ListView {
            id: headerList
            anchors.fill: parent
            orientation: ListView.Horizontal
            interactive: false
            model: m_header

            delegate: Item{
                width: m_header[index].columnSpan * d.spanSize
                height: headerHeight
                Text {
                    height: parent.height
                    anchors{left: parent.left; right: parent.right; leftMargin: parent.width * 0.05}

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: m_header[index].horizontalAlign
                    color: tableView.headerTextColor
                    font.pixelSize: height * tableView.headerFontSize / 100
                    font.bold: tableView.headerFontBold
                    wrapMode: Text.WordWrap

                    text: m_header[index].title
                    maximumLineCount: 2
                    elide: Text.ElideRight
                }
            }
        }

        Rectangle{width: parent.width; height: d.separatorHeight; color: "black"; anchors.top: headerList.bottom}
    }

    ListView {
        id: dataList
        anchors.fill: parent
        header: tableHeader
        headerPositioning: ListView.OverlayHeader
        clip: true
        boundsBehavior: Flickable.DragAndOvershootBounds
        ScrollIndicator.vertical: ScrollIndicator {id: scrollIndicator; width: dataList.width*0.01; anchors{top: parent.top; right: parent.right; bottom: parent.bottom} onActiveChanged: active = hideScrollIndicator ? active : true; active: hideScrollIndicator ? active : true}
        model: m_model
        delegate: Item{
            id: rowDelegate
            width: d.rowWidth
            height: d.rowHeight
            Rectangle{
                id: bgColor
                anchors.top:parent.top
                width: parent.width
                height: parent.height - separatorLine.height
                color:getColor()
                function getColor(){
                    if(isHeighlight && index === dataList.currentIndex)
                        return highlightRowColor
                    else if(model.rowBackground)
                        return model.rowBackground
                    else if(isChessBackground && index % 2)
                        return  "#40AEAEAE"
                    return rowBackgroundColor
                }
            }
            Rectangle{id: separatorLine; width: parent.width; height: d.separatorHeight; anchors.top: bgColor.bottom; color: constant.grey}
            readonly property var rowData : model
            readonly property QtObject modelData: QtObject{ readonly property var rowTextColor: model.rowTextColor}

            MouseArea {
                anchors.fill: parent
                property bool isHold: false
                onPressed: isHold = false
                onClicked: {
                    dataList.currentIndex = index
                    tableView.click(index)
                }
                onDoubleClicked: {
                    dataList.currentIndex = index
                    tableView.doubleClick(index)
                }
                onReleased: {
                    if(isHold)
                        tableView.pressAndHoldRelise();
                }
                onPressAndHold: {
                    isHold = true
                    dataList.currentIndex = index
                    tableView.pressAndHold(index)
                }
            }

            Row{
                id:row
                spacing: 0
                Repeater {
                    id: lineItem
                    model: columnCount
                    Loader {
                        id: delegateLoader
                        width: m_header[index].columnSpan * d.spanSize
                        height: d.rowHeight
                        sourceComponent: m_header[index].delegate ? m_header[index].delegate : defaultDelegate
                        property QtObject columnData: QtObject {
                            readonly property var value: rowDelegate.rowData[m_header[index].role]
                            readonly property int itemAlign: m_header[index].horizontalAlign
                            readonly property int itemIndex: rowDelegate.rowData.index
                            readonly property bool locateField: m_header[index].locateField
                        }
                    }
                }
            }

            Component{
                id: defaultDelegate
                Text {
                    height: parent.height
                    anchors{left: parent.left; right: parent.right; leftMargin: parent.width * 0.05}

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: columnData.itemAlign
                    color: modelData.rowTextColor ? modelData.rowTextColor : tableView.columnTextColor
                    font.pixelSize: height * 0.9 * tableView.columnFontSize / 100
                    font.bold: tableView.columnFontBold
                    wrapMode: Text.WordWrap
                    text: columnData.locateField ? textFromValue(columnData.value, Qt.locale(AppSettings.currentLocale)) + AppSettings.countryUpdater : columnData.value
                    maximumLineCount: 2
                    elide: Text.ElideRight
                }
            }
        }
    }
    Loader{
        id: disableLoader
        width: parent.width
        height: parent.height - tableHeader.height
        anchors.top: tableHeader.bottom
        sourceComponent: tableView.block ? disableComponent : undefined
    }
    QtObject {
        id: d
        property real rowHeight: dataList.height / visibleRow
        property real rowWidth: dataList.width
        property real separatorHeight: rowHeight / 40
        property real spanSize

        function initWidth()
        {
            var totalSpan = 0
            for(var i = 0; i < columnCount; i++)
                totalSpan += (m_header[i].columnSpan * columnSpanCoef)
            spanSize = rowWidth / totalSpan
        }
    }

    Component{
        id: disableComponent
        Rectangle{
            color: "#80FFFFFF"
            MouseArea{anchors.fill: parent}
        }
    }
}
