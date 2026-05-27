import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 1200 // Made it slightly wider to fit the buttons
    height: 700
    visible: true
    title: qsTr("Journal Dashboard")

    // NEW: We need a variable to remember which row we are currently editing.
    // -1 means we are creating a NEW entry, not editing an old one.
    property int currentEditIndex: -1

    ListModel {
        id: journalDatabase
        ListElement { entryDate: "2026-05-26"; mood: "Great"; ego: false; prod: true; win: "Learned QML"; lesson: "Layouts are easy"; focus: "Databases" }
        ListElement { entryDate: "2026-05-25"; mood: "Bad"; ego: true; prod: false; win: "None"; lesson: "Need more sleep"; focus: "Resting" }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        RowLayout {
            spacing: 10
            Text { text: "Filters:"; font.bold: true; font.pixelSize: 16 }
            Button { text: "Bad Days" }
            Button { text: "Productive Streaks" }
            Button { text: "Ego Triggers" }
        }

        // Table Header
        RowLayout {
            Layout.fillWidth: true
            Text { text: "Date"; font.bold: true; Layout.preferredWidth: 100 }
            Text { text: "Mood"; font.bold: true; Layout.preferredWidth: 80 }
            Text { text: "Ego Trigger"; font.bold: true; Layout.preferredWidth: 80 }
            Text { text: "Productive"; font.bold: true; Layout.preferredWidth: 80 }
            Text { text: "Main Win"; font.bold: true; Layout.preferredWidth: 150 }
            Text { text: "Main Lesson"; font.bold: true; Layout.preferredWidth: 150 }
            Text { text: "Tomorrow Focus"; font.bold: true; Layout.fillWidth: true }
            Text { text: "Actions"; font.bold: true; Layout.preferredWidth: 120 } // NEW: Header for buttons
        }

        // The Actual Table
        ListView {
            id: tableView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: journalDatabase
            spacing: 10

            delegate: RowLayout {
                width: tableView.width

                Text { text: model.entryDate; Layout.preferredWidth: 100 }
                Text { text: model.mood; Layout.preferredWidth: 80 }
                CheckBox { checked: model.ego; enabled: false; Layout.preferredWidth: 80 }
                CheckBox { checked: model.prod; enabled: false; Layout.preferredWidth: 80 }
                Text { text: model.win; Layout.preferredWidth: 150; elide: Text.ElideRight }
                Text { text: model.lesson; Layout.preferredWidth: 150; elide: Text.ElideRight }
                Text { text: model.focus; Layout.fillWidth: true; elide: Text.ElideRight }

                // NEW: Edit and Delete Buttons for each row
                RowLayout {
                    Layout.preferredWidth: 120
                    spacing: 5

                    Button {
                        text: "Edit"
                        onClicked: {
                            // 1. Save the row number we are editing
                            currentEditIndex = index

                            // 2. Pre-fill the popup with this row's data
                            inputDate.text = model.entryDate
                            inputMood.displayText = model.mood
                            inputEgo.checked = model.ego
                            inputProd.checked = model.prod
                            inputWin.text = model.win
                            inputLesson.text = model.lesson
                            inputFocus.text = model.focus

                            // 3. Open the popup
                            entryPopup.open()
                        }
                    }

                    Button {
                        text: "X" // X for Delete
                        // The ListModel has a built-in remove() command
                        onClicked: journalDatabase.remove(index)
                    }
                }
            }
        }

        Button {
            text: "+ Add Daily Record"
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 16
            onClicked: {
                currentEditIndex = -1 // -1 means "New Entry"

                // Clear the form before opening
                inputDate.text = ""
                inputWin.text = ""
                inputLesson.text = ""
                inputFocus.text = ""
                inputEgo.checked = false
                inputProd.checked = false

                entryPopup.open()
            }
        }
    }

    // --- THE POPUP ---
    Popup {
        id: entryPopup
        width: 400
        height: 550
        anchors.centerIn: parent
        modal: true
        focus: true

        background: Rectangle {
            color: "white"
            border.color: "gray"
            radius: 10
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 20
            spacing: 10

            // NEW: The title changes depending on if we are editing or adding
            Text {
                text: currentEditIndex === -1 ? "New Daily Review" : "Edit Daily Review"
                font.pixelSize: 20; font.bold: true; Layout.alignment: Qt.AlignHCenter
            }

            TextField { id: inputDate; placeholderText: "Date (e.g., 2026-05-27)"; Layout.fillWidth: true }
            ComboBox { id: inputMood; model: ["Great", "Okay", "Bad"]; Layout.fillWidth: true }
            CheckBox { id: inputEgo; text: "Ego Triggered?" }
            CheckBox { id: inputProd; text: "Productive Day?" }

            TextArea { id: inputWin; placeholderText: "Main Win..."; Layout.fillWidth: true; Layout.fillHeight: true }
            TextArea { id: inputLesson; placeholderText: "Main Lesson..."; Layout.fillWidth: true; Layout.fillHeight: true }
            TextArea { id: inputFocus; placeholderText: "Tomorrow's Focus..."; Layout.fillWidth: true; Layout.fillHeight: true }

            Button {
                // NEW: Button text changes contextually
                text: currentEditIndex === -1 ? "Save New Entry" : "Update Entry"
                Layout.fillWidth: true

                onClicked: {
                    if (currentEditIndex === -1) {
                        // WE ARE ADDING A NEW ENTRY
                        journalDatabase.append({
                            entryDate: inputDate.text,
                            mood: inputMood.currentText,
                            ego: inputEgo.checked,
                            prod: inputProd.checked,
                            win: inputWin.text,
                            lesson: inputLesson.text,
                            focus: inputFocus.text
                        })
                    } else {
                        // WE ARE EDITING AN EXISTING ENTRY (using setProperty)
                        journalDatabase.setProperty(currentEditIndex, "entryDate", inputDate.text)
                        journalDatabase.setProperty(currentEditIndex, "mood", inputMood.currentText)
                        journalDatabase.setProperty(currentEditIndex, "ego", inputEgo.checked)
                        journalDatabase.setProperty(currentEditIndex, "prod", inputProd.checked)
                        journalDatabase.setProperty(currentEditIndex, "win", inputWin.text)
                        journalDatabase.setProperty(currentEditIndex, "lesson", inputLesson.text)
                        journalDatabase.setProperty(currentEditIndex, "focus", inputFocus.text)
                    }

                    entryPopup.close()
                }
            }
        }
    }
}