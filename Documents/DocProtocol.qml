import QtQuick 2.9
import QtQuick.Layouts 1.3
import "../BaseElements" as BaseElements
import CreateOptics 1.0

BaseElements.BasePage{
    headerHeight: 0

    centerData:
        Loader{
        id: docLoader
        anchors.fill: parent
        sourceComponent: undefined
    }

    Component{
        id: docProtocol
        BaseElements.BaseTableView{
            m_model: DocumentProtocol{}
            m_header: [
                BaseElements.BaseColumnComponent{title: qsTr("Information"); role: "information"},
                BaseElements.BaseColumnComponent{title: qsTr("Command"); role: "command"}
            ]
        }
    }

    Component{
        id: sessionReport
        BaseElements.BaseTableView{
            columnSpanCoef: 1.0
            m_model: SessionReport{}
            m_header: [
                BaseElements.BaseColumnComponent{title: qsTr("Name"); role: "name"},
                BaseElements.BaseColumnComponent{title: qsTr("Open session"); role: "begin_session"},
                BaseElements.BaseColumnComponent{title: qsTr("Close session"); role: "end_session"}
            ]
        }
    }

    sliceData: GridLayout{
        id: grid
        width: parent.width * 0.97
        height: parent.height * 0.97
        anchors.centerIn: parent
        rows: 2
        columns: 1
        rowSpacing: 1

        BaseElements.BaseButton{
            id: protocolBttn
            text: qsTr("Protocol")
            Layout.fillWidth: true
            height: 50
            textSize: constant.sTextSize
            color: "#093daa"
            radius: 0
            onClicked: {docLoader.sourceComponent = docProtocol}
        }

        BaseElements.BaseButton{
            text: qsTr("Lol")
            Layout.fillWidth: true
            height: 50
            textSize: constant.sTextSize
            color: "#093daa"
            radius: 0
            onClicked: {docLoader.sourceComponent = sessionReport}
        }
        Item { Layout.fillHeight: true }
    }
}
