import QtQuick 2.0
import QtQml 2.2

Item {
    property bool isClock: true
    property bool isTimer: false

    property real hour: 0
    property real min: 0
    property real sec: 0

    property bool blinck: false

    property bool startTimer: false
    property bool stopTimer: true
    property bool pauseTimer: false

    Text {
        id: hours
        color: isClock ? constant.grey : constant.red
        font.bold: true
        font.pixelSize: isClock ? parent.height * 0.03 : parent.height * 0.05
        anchors.centerIn: parent
        text: isClock ? Qt.formatTime(new Date(), "hh:mm:ss")
                      : (((hour < 10) ? ('0' + hour) : hour)
                         + ':'
                         + ((min < 10) ? ('0' + min) : min)
                         + ':'
                         + ((sec < 10 ? ('0' + sec) : sec)))
    }

    Timer {
        id: timerClock
        interval: 1000
        repeat: true
        running: isClock ? true : false
        onTriggered: hours.text = Qt.formatTime(new Date(),"hh:mm:ss")
    }

    Timer{
        id: timerTimer
        interval: 1000
        repeat: true
        running: false
        onTriggered: {hours.visible = true; startTime(sec++);
            if(min === signalWarning)
                d.startSirena()
        }
    }

    Timer{
        interval: 700
        repeat: true
        running: !timerTimer.running
        onTriggered: {
            if(isTimer && stopTimer)
            {
                isClock = false;
                if(blinck){
                    hours.visible = true
                    blinck = false
                }
                else{
                    hours.visible = false
                    blinck = true
                }
            }
        }

    }

    QtObject{
        id: d
        function startSirena(){
            settingsController.play()
        }
    }

    Timer{
        id: warning
        running: false
        repeat: false
        interval: 10000
        onTriggered: settingsController.play()
    }

    function start(){
        if(isTimer)
        {
            isClock = false
            if(!startTimer){
                timerTimer.start()
                startTimer = true
                stopTimer = false
                pauseTimer = false
            }
        }
    }

    function stop(){
        if(isTimer)
        {
            isClock = false
            if(startTimer || pauseTimer){
                timerTimer.stop()
                hour = 0
                min = 0
                sec = 0
                startTimer = false
                stopTimer = true
                pauseTimer = false
            }
        }
    }

    function pause(){
        if(isTimer)
        {
            isClock = false
            if(startTimer){
                timerTimer.stop()
                startTimer = false
                pauseTimer = true
                stopTimer = false
            }
        }
    }

    function startTime(s){
        if (s >= 59){
            sec = 0
            min++
        }

        if (min >= 60){
            min = 0
            hour++
        }

        if(hour >= 24){
            hour = 0
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(isTimer && pauseTimer){
                isClock = false
                stop()
            }
        }
    }
}
