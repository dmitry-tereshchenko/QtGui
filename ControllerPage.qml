import QtQuick 2.9
import QtQuick.Controls 2.0
import "BaseElements" as BaseElements
import CreateOptics 1.0

BaseElements.BasePage{
    id: controllerPage
    headerData: Rectangle{
        anchors.fill: parent
        color: "white"
        Rectangle{
            anchors.bottom: parent.bottom
            color: constant.grey
            height: 1
            width: parent.width
        }

        Item{
            anchors{
                right: parent.right
                rightMargin: parent.width * 0.15
                verticalCenter: parent.verticalCenter
            }
            implicitWidth: clock.width
            implicitHeight: clock.height

            BaseElements.Clock{
                id: timer
                height: controllerPage.height
                width: controllerPage.width * 0.1
                isTimer: true
            }

            BaseElements.Clock{
                id: clock
                height: controllerPage.height
                width: controllerPage.width * 0.1
                anchors.left: timer.right
                anchors.leftMargin: parent.width * 0.5
                isClock: true
            }
        }

        BaseElements.WorkStatus{
            id: lightsView
            height: parent.height
            width: parent.width * 0.18
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: parent.width * 0.06
            }
        }

        BaseElements.StartButton{
            id: startBttn
            width: height
            height: parent.height * 0.7
            anchors.centerIn: parent
            onClick: d.onClickStart(this)
        }
    }

    sliceData:
        Switch{
        id: connectToPort
        Connection{id: connection}
        anchors.horizontalCenter: parent.horizontalCenter
        checked: false
        onClicked: {
            if(checked && startBttn.isStopState)
                connection.connect()

            if(!checked && startBttn.isStopState)
                connection.disconnect()

            else if(!checked && !startBttn.isStopState)
                checked = true
        }
        Connections{
            target: connection
            onConnectChanged : {d.onConnect()}
            onDisconnectChanged : {d.onDisconnect()}
        }
    }

    centerData: Rectangle{
        anchors.fill: parent
        color: "#ecf0f1"
        Rectangle{
            id: animRect
            width: parent.width * 0.4
            height: parent.height * 0.6
            color: "transparent"
            border.color: constant.grey
            border.width: 1

            Rectangle{
                id: baseEng
                width: parent.width * 0.3
                height: width
                radius: height * 0.5
                color: parent.color
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.6) - height * 0.5
                anchors.horizontalCenter: parent.horizontalCenter
                border.color: constant.grey
                border.width: 2
                Rectangle{
                    anchors.centerIn: parent
                    width: parent.width * 0.15
                    height: width
                    color: "white"
                    border.color: constant.grey
                    border.width: 1
                }
                RotationAnimation on rotation{
                    id: baseEngAnim
                    loops: Animation.Infinite
                    running: false
                    from: 0
                    to: 360
                }
            }

            Rectangle{
                id: dualEng_1
                width: baseEng.width * 0.5
                height: width
                radius: height * 0.5
                color: parent.color
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.4) - height * 0.5
                anchors.left: parent.left
                anchors.leftMargin: parent.width * 0.15
                border.color: constant.grey
                border.width: 2
                Rectangle{
                    width: parent.width * 0.15
                    height: parent.width * 0.55
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.verticalCenter
                    color: "white"
                    border.color: constant.grey
                    border.width: 1
                }
                RotationAnimation on rotation{
                    id: dualEngAnim
                    loops: Animation.Infinite
                    running: false
                    from: 0
                    to: 360
                }
            }

            Rectangle{
                id: dualEng_2
                width: baseEng.width * 0.5
                height: width
                radius: height * 0.5
                color: parent.color
                anchors.top: parent.top
                anchors.topMargin: (parent.height * 0.4) - height * 0.5
                anchors.right: parent.right
                anchors.rightMargin: parent.width * 0.15
                border.color: constant.grey
                border.width: 2
                Rectangle{
                    width: parent.width * 0.15
                    height: width
                    radius: height
                    anchors.centerIn: parent
                    color: "white"
                    border.color: constant.grey
                    border.width: 1
                }
            }
        }

        Item
        {
            anchors.centerIn: parent
            width: parent.width * 0.25
            height: parent.height * 0.7

            Slider{
                id: baseEngine
                anchors.centerIn: parent
                orientation: Qt.Vertical
                to: defaultSettings.rotateBaseEngineCount
                from: 0.0
                stepSize: defaultSettings.stepBaseEngineCount
                value: 0.0
                enabled: false
                height: parent.height
                onValueChanged: {animManager.recalculateTurnovers(this, baseEngAnim); led.runEngine(Command.BASE_ENGINE, d.recalculateValue(rotateCountBaseEngine, value))}
            }

            Slider{
                id: secondEngine
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                height: parent.height * 0.8
                orientation: Qt.Vertical
                to: defaultSettings.rotateSecondaryEngineCount
                from: 0.0
                stepSize: defaultSettings.stepSecondaryEngineCount
                value: 0.0
                enabled: false
                onValueChanged: {animManager.recalculateTurnovers(this, dualEngAnim); thirdEngine.value = value; led.runEngine(Command.DUAL_ENGINE, d.recalculateValue(rotateCountBaseEngine, value))}
            }

            Slider{
                id: thirdEngine
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: parent.height * 0.8
                orientation: Qt.Vertical
                to: defaultSettings.rotateSecondaryEngineCount
                from: 0.0
                stepSize: defaultSettings.stepSecondaryEngineCount
                value: 0.0
                enabled: secondEngine.enabled
                onValueChanged: {animManager.recalculateTurnovers(this, dualEngAnim); secondEngine.value = value}
            }
        }
    }

    QtObject{
        id: d
        function onDisconnect(){
            lightsView.currentIndex = 0 ///< Будет гореть красный
            startBttn.enabled = false
            connectToPort.checked = false
            baseEngine.value = 0
            baseEngine.enabled = false
            secondEngine.enabled = false
        }

        function onConnect(){
            lightsView.currentIndex = 0
            lightsView.incrementCurrentIndex()
            startBttn.enabled = true
            if(defaultSettings.enabledBaseEngine && defaultSettings.enabledSecondaryEngine){
                baseEngine.enabled = true
                secondEngine.enabled = true
            }
        }

        function onClickStart(button){
            if(button.state === button.stop())
            {
                timer.start()
                button.state = button.start()
                button.startState()
                lightsView.incrementCurrentIndex()
                animManager.startAnim()
            }

            else
            {
                lightsView.decrementCurrentIndex()
                timer.pause();
                button.state = button.stop()
                button.stopState()
                animManager.stopAnim()
            }
        }

        function recalculateValue(rotateCount, value){
            return (255 / rotateCount) * value
        }
    }

    QtObject{
        id: animManager

        function startAnim(){
            if(baseEngine.value > 0){
                baseEngAnim.duration = (60 / baseEngine.value) * 1000
                baseEngAnim.start()
            }
            if(secondEngine.value > 0){
                dualEngAnim.duration = (60 / secondEngine.value) * 1000
                dualEngAnim.start()
            }
        }

        function stopAnim(){
            baseEngAnim.stop()
            dualEngAnim.stop()
        }

        function recalculateTurnovers(engine, animation){
            if((startBttn.state !== startBttn.stop()) && (engine.value > 0)){
                animation.duration = (60 / engine.value) * 1000
                if(animation.running !== true){
                    animation.start()
                }
                else animation.restart()
            }
            else
                animation.stop()
        }
    }
}
