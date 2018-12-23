import QtQuick 2.0

Item{
    id: button
    signal click()

    property bool isStartState: false
    property bool isStopState: true
    property bool isPauseState: false

    state: stop()
    enabled: false

    states: [
        State {
            name: start()
            PropertyChanges {
                target: loadImage
                sourceComponent: pauseImage
            }
        },

        State {
            name: stop()
            PropertyChanges {
                target: loadImage
                sourceComponent: startImage
            }
        }
    ]

    Loader{id: loadImage; anchors.fill: parent; sourceComponent: startImage}

    Component{
        id: startImage
        Image {
            visible: button.enabled ? 1 : 0
            source: imagePath("startButton.png")
        }
    }

    Component{
        id: pauseImage
        Image {
            source: imagePath("PauseButton.png")
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {click()}
    }

    function start()
    {
        return "start"
    }


    function stop()
    {
        return "stop"
    }

    function startState(){
        isStartState = true
        isStopState = false
        isPauseState = false
    }

    function stopState(){
        isStopState = true
        isStartState = false
        isPauseState = false
    }

    function currentState(){
        isPauseState = true
        isStartState = false
        return state.toString()
    }
}
