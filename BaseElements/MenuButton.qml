import QtQuick 2.0

Canvas {
    property var heightButton: parent.height
    property var widthButton: heightButton

    width: widthButton
    height: heightButton

    signal click()

    onPaint: {
        var ctx = getContext('2d')
        ctx.fillStyle = 'white'
        ctx.fillRect(0, 0, width, height)

        var left = width * 0.25
        var right = width * 0.75
        var vCenter = height * 0.5
        var vDelta = height / 6

        ctx.lineCap = "square"
        ctx.lineWidth = vDelta * 0.4
        ctx.strokeStyle = 'black'

        ctx.beginPath()
        ctx.moveTo(left, vCenter - vDelta)
        ctx.lineTo(right, vCenter - vDelta)
        ctx.moveTo(left, vCenter)
        ctx.lineTo(right, vCenter)
        ctx.moveTo(left, vCenter + vDelta)
        ctx.lineTo(right, vCenter + vDelta)
        ctx.stroke()
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {click()}
    }
}
