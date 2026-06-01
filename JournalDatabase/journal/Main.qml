import QtQuick
import QtQuick.Controls
import QtQuick.Layouts


Window {
    width: 1200 // Made it slightly wider to fit the buttons
    height: 700
    visible: true
    color: "lightblue"
    title: qsTr("Journal Dashboard")

    // NEW: We need a variable to remember which row we are currently editing.
    // -1 means we are creating a NEW entry, not editing an old one.
    property int currentEditIndex: -1
    // --- HELPER FUNCTIONS ---
        // Converts the ListModel to a JSON string and sends it to C++
        function saveToDisk() {
            var datalist = []
            for (var i = 0; i < journalDatabase.count; i++) {
                datalist.push(journalDatabase.get(i))
            }
            var jsonString = JSON.stringify(datalist)
            Backend.saveDatabase(jsonString) // Calling the C++ function!
        }

        // Loads the JSON string from C++, parses it, and fills the ListModel
        function loadFromDisk() {
            var jsonString = Backend.loadDatabase() // Calling the C++ function!
            var datalist = JSON.parse(jsonString)

            journalDatabase.clear() // Empty the fake data
            for (var i = 0; i < datalist.length; i++) {
                journalDatabase.append(datalist[i])
            }
        }

        // NEW: This built-in signal runs exactly once when the app opens
        Component.onCompleted: {
            loadFromDisk()
        }

    ListModel {
        id: journalDatabase
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 15

        RowLayout {
            spacing: 10
            Text { text: "Filters:"; font.bold: true; font.pixelSize: 20 }
            Button { text: "Bad Days"; width: 20;}
            Button { text: "Productive Streaks"; width: 20}
            Button { text: "Ego Triggers"; width: 20 }
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

            // Replace your existing delegate: RowLayout { ... } with this:

            delegate: Rectangle {
                width: tableView.width
                height: 50 // Fixed height for a cleaner look
                radius: 8 // Rounded corners for the modern feel
                color: "white"
                border.color: "#E0E0E0" // A very light gray border

                // We put the RowLayout INSIDE the Rectangle card
                RowLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 15
                    anchors.rightMargin: 15

                    // We make the text slightly muted for a cleaner aesthetic
                    Text { text: model.entryDate; color: "#333333"; font.bold: true; Layout.preferredWidth: 100 }
                    Text { text: model.mood; color: "#555555"; Layout.preferredWidth: 80 }

                    // Using custom icons or simpler text instead of full checkboxes for a cleaner table
                    Text { text: model.ego ? "⚠️ Yes" : "-"; Layout.preferredWidth: 80 }
                    Text { text: model.prod ? "✅ Yes" : "-"; Layout.preferredWidth: 80 }

                    Text { text: model.win; color: "#555555"; Layout.preferredWidth: 150; elide: Text.ElideRight }
                    Text { text: model.lesson; color: "#555555"; Layout.preferredWidth: 150; elide: Text.ElideRight }
                    Text { text: model.focus; color: "#555555"; Layout.fillWidth: true; elide: Text.ElideRight }

                    RowLayout {
                        Layout.preferredWidth: 120
                        spacing: 5

                        // Material style makes these buttons look flat and modern automatically
                        Button {
                            text: "Edit"
                            flat: true // Makes the button background transparent until hovered
                            onClicked: {
                                currentEditIndex = index
                                inputDate.text = model.entryDate
                                inputMood.displayText = model.mood
                                inputEgo.checked = model.ego
                                inputProd.checked = model.prod
                                inputWin.text = model.win
                                inputLesson.text = model.lesson
                                inputFocus.text = model.focus
                                entryPopup.open()
                            }
                        }
                        Button {
                            text: "Delete"
                            flat: true
                            // Adding Material color specifically to the delete button text
                            Material.foreground: Material.Red
                            onClicked: {
                                journalDatabase.remove(index)
                                saveToDisk()
                            }
                        }
                    }
                }
            }
            }
        }

        Button {
            text: "+ Add Daily Record"
            Layout.alignment: Qt.AlignHCenter
            font.pixelSize: 16
            onClicked: {
                currentEditIndex = -1
                // NEW: Automatically grab today's date and format it!

                inputDate.text = Qt.formatDateTime(new Date(), "yyyy-MM-dd")

                // Clear the other fields as usual

                inputWin.text = ""

                inputLesson.text = ""

                inputFocus.text = ""

                inputEgo.checked = false

                inputProd.checked = false
                entryPopup.open()
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
                            saveToDisk()
                        }
                    }
                }
            }
        }