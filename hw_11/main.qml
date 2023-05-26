import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import com.my.organizer 1.0
//import com.my.tablemodel 1.0

Window {
    visible: true
    modality: Qt.WindowModal
    minimumHeight: 240
    minimumWidth: 400
    maximumHeight: 240
    maximumWidth: 400
    height: 240
    width: 400

    Organizer{
        id: organizer
        onIndexChanged: {
            title.text = currentTaskTitle;
            deadline.text = currentTaskDeadline;
            priority.value = currentTaskPriority;
        }
        onFileOpenError: errorFileDialog.visible = true

    }

    MessageDialog{
        id: emptyTaskDialog
        icon: StandardIcon.Critical
        title: qsTr("Empty task")
        text: qsTr("Need to add title and deadline for a task")
        Component.onCompleted: visible = false
    }

    Rectangle{
        id: background
        anchors.fill: parent
        color: "grey"
    }

    GridLayout{
        id: fields
        rows: 4
        columns: 3
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 10
        anchors.topMargin: 10

        Label{
            id: titleLabel
            text: qsTr("Title")
            Layout.row: 0
            Layout.column: 0
        }

        TextField{
                id: title
                Layout.row: 0
                Layout.column: 1
                width: 50
                height: 50
                selectByMouse: true
                text: organizer.currentTaskTitle
        }

        Label{
            id: deadlineLabel
            text: qsTr("Deadline")
            Layout.row: 1
            Layout.column: 0
        }


        TextField{
                id: deadline
                Layout.row: 1
                Layout.column: 1
                width:50
                height:50
                horizontalAlignment: "AlignHCenter"
                Layout.maximumWidth: 120
                inputMask: "00.00.0000"
                selectByMouse: true
                onFocusChanged: cursorPosition = 0
                text: organizer.currentTaskDeadline
                ToolTip{
                    id: wrongDateToolTip

                    visible: false
                    timeout: 1000
                    contentItem: Text{
                        text: qsTr("Wrong date!")
                        color: "red"
                    }
                    background: Rectangle {
                            border.color: "red"
                        }
                }

                onEditingFinished: {
                    var dateExp = /^(?:(?:31(.)(?:0?[13578]|1[02]))\1|(?:(?:29|30)(.)(?:0?[13-9]|1[0-2])\2))(?:(?:1[6-9]|[2-9]\d)?\d{4})$|^(?:29(.)0?2\3(?:(?:(?:1[6-9]|[2-9]\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\d|2[0-8])(.)(?:(?:0?[1-9])|(?:1[0-2]))\4(?:(?:1[6-9]|[2-9]\d)?\d{4})$/;
                    if (dateExp.test(text))
                        return;
                    else{
                        console.log(text);
                        wrongDateToolTip.visible = true;
                        text = ""
                    }
                }

        }

        Label{
            id: priorityLabel
            text: qsTr("Priority")
            Layout.row: 2
            Layout.column: 0
        }

        SpinBox{
                id: priority
                Layout.row: 2
                Layout.column: 1
                Layout.maximumWidth: 120
                editable: true
                height:50
                from: 0
                to: 10
                value: organizer.currentTaskPriority
        }

        Label{
            text: "Total tasks:"
            Layout.row: 3
            Layout.column: 0
        }

        TextEdit{
            Layout.row: 3
            Layout.column: 1
            id: totalTasks
            text: organizer.totalTasks
        }

        Button{
            Layout.row: 0
            Layout.column: 2
            text: qsTr("Show table")
            onClicked: {
                tableDialog.open()
            }
        }

    }



    RowLayout{
        id: navigationLayout
        anchors.bottom: parent.bottom
        anchors.leftMargin: 10
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter

        Button{
            id: previousTask
            text: qsTr("<< Previous")
            Layout.column: 0
            onClicked: organizer.prevTask()
        }
        Label{
            id: currentIndexLabel
            text: organizer.index >=0 ? organizer.index : ""
            horizontalAlignment: "AlignHCenter"
            Layout.column: 1
            Layout.minimumWidth: 30
        }

        Button{
            id: nextTask
            text: qsTr("Next >>")
            Layout.column: 2
            onClicked: organizer.nextTask()
        }

        Button{
            id: addTask
            text: qsTr("Add task")
            Layout.column: 3
            onClicked:{
                if (title.text != "" && deadline.text != "..") organizer.addNewTask(title.text,deadline.text,priority.value);
                else {
                    emptyTaskDialog.visible = true;
                }
            }
        }
    }

    Dialog{
        id: tableDialog

        width: 400
        height: 600

        title: qsTr("Database")
        onAccepted: tableDialog.close()

        TableView{
            id: tableView
            property var columnWidths: [30, 200, 90, 30]
            anchors.fill: parent
            columnSpacing: 2
            rowSpacing: 2
            clip: true

            columnWidthProvider: function (column) { return columnWidths[column] }
            model: organizer.model
            delegate: Rectangle {
                implicitHeight: 30
                implicitWidth: 30
                Text {
                    id: txt
                    text: display
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

       }
    }

}
