import QtQuick 2.0

Item{
    signal click(var index)
    property real sizeCoeficient: 0.9
    ListView{
        id: listView
        model: headerModel
        anchors.fill: parent
        orientation: ListView.Horizontal
        currentIndex: swipeView.currentIndex
        interactive: false
        delegate: BaseButton{
            id: baseButton
            height: parent.height
            width: height * 1.8
            radius: 0
            color: "transparent"
            image: imagePath(headerImage)
            hImageAlign: Image.AlignHCenter
            onPressed: imageSize = imageSize * sizeCoeficient
            onReleased: {imageSize = imageSize / sizeCoeficient; click(index); animStart.start()}
            Rectangle{
                id: footer
                width: parent.width
                height: parent.height * 0.08
                anchors.horizontalCenter: parent.horizontalCenter
                color: constant.grey
                anchors.bottom: parent.bottom
                visible: listView.currentIndex === index ? true : false
                PropertyAnimation{
                    id: animStart
                    target: footer
                    property: "width"
                    from: footer.width
                    to: footer.width * 0.4
                    easing.type: Easing.InOutQuad; duration: 100
                    onStopped: animStop.start()
                }
                PropertyAnimation{
                    id: animStop
                    target: footer
                    property: "width"
                    from: footer.width
                    to: footer.width / 0.4
                    easing.type: Easing.InOutQuad; duration: animStart.duration
                }
            }
        }
    }
}
