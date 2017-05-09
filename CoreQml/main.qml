import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQml.Models 2.1
import QtQuick.Dialogs 1.2
import "../CoreQml"
import ControllerLib 1.0

ApplicationWindow {
    id: mainWindow
    visible: true

    property real downloadProgress: 0
    property bool imageLoading: false
    property bool editMode: false

    width: 800
    //height: 480
    height: 540
    color: "#d5d6d8"

    Component.onCompleted: {
        if(Controller.getApiKey() === "")
            statusBar.text = "No Api key"
    }

    menuBar: MenuBar {
        Menu { title: "File"
            MenuItem { action: exitAction }
        }

        Menu { title: "Edit"
            MenuItem { action: privateAPIKeyAction }
        }

        Menu { title: "Results per page"; enabled: true
            MenuItem {
                id: menuItem100; text: "100"; checkable: true; checked: true
                exclusiveGroup: resultPerPageGroup; onCheckedChanged: Controller.setPerPage("100")
            }
            MenuItem {
                id: menuItem200; text: "200"; checkable: true
                exclusiveGroup: resultPerPageGroup; onCheckedChanged: Controller.setPerPage("200")
            }
            MenuItem {
                id: menuItem300; text: "300"; checkable: true; exclusiveGroup: resultPerPageGroup
                onCheckedChanged: Controller.setPerPage("300")
            }
            MenuItem {
                id: menuItem4; text: "400"; checkable: true; exclusiveGroup: resultPerPageGroup
                onCheckedChanged: Controller.setPerPage("400")
            }
            MenuItem {
                id: menuItem500; text: "500"; checkable: true
                exclusiveGroup: resultPerPageGroup; onCheckedChanged: Controller.setPerPage("500")
            }
        }
    }

    statusBar: StatusBar {
        RowLayout {
            anchors.fill: parent
            Label { id: statusBar; text: " " }
        }
    }

    ExclusiveGroup { id: resultPerPageGroup }

    Action { id: exitAction; text: "Exit"; onTriggered: { Qt.quit() } }
    Action { id: privateAPIKeyAction; text: "Enter API key..."
        onTriggered: {
            var key = Controller.getApiKey();
            if(key != "") {
                flickrApiKeyTextField.text = key;
                flickrApiKeyTextField.selectAll()
            }
            apiKeyDialog.open()
        }
    }

    Dialog {
        id: apiKeyDialog; title: qsTr("Flickr API Key");
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        onVisibleChanged: flickrApiKeyTextField.forceActiveFocus()

        Column { anchors.fill: parent
            Text { text: "Enter your Flickr API key" }
            TextField { id: flickrApiKeyTextField
                Keys.onEnterPressed: {
                    event.accepted = true; apiKeyDialog.close();
                    Controller.setApiKey(flickrApiKeyTextField.text)
                }
            }
        }

        onButtonClicked: {
            if(clickedButton === StandardButton.Ok) {
                Controller.setApiKey(flickrApiKeyTextField.text)
            }
        }
    }

    // TODO
    MessageDialog {
        id: apiKeyIsValidDialog; objectName: "messageDialog"
        title: qsTr("Flickr API key"); visible: false
    }

    Rectangle {
        focus: true
        Keys.onBackPressed: {
            event.accepted = true
            backButton.clicked()
        }
    }

    DelegateModel {
        id: albumVisualModel; model: RssListModel; delegate: AlbumDelegate { }
    }

    GridView {
        id: albumView; width: parent.width; height: parent.height; cellWidth: 210
        cellHeight: 220; model: albumVisualModel.parts.album; visible: albumsShade.opacity != 1.0
    }

    Column {
        spacing: 20
        anchors { bottom: parent.bottom; right: parent.right; rightMargin: 20; bottomMargin: 20 }

        Button {
            id: newButton; label: qsTr("Add"); /*rotation: 3;*/rotation: 0; anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                mainWindow.editMode = false
                Controller.createDummyListModel();
                albumView.positionViewAtIndex(albumView.count - 1, GridView.Contain)
            }
        }

        Button {
            id: deleteButton; label: qsTr("Edit")
            /*rotation: -2*/ rotation: 0; onClicked: mainWindow.editMode = !mainWindow.editMode
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: quitButton; label: qsTr("Quit"); /*rotation: -2*/ rotation: 0; onClicked: Qt.quit()
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Rectangle {
        id: albumsShade; color: mainWindow.color; width: parent.width
        height: parent.height; opacity: 0.0
    }

    ListView {
        anchors.fill: parent; model: albumVisualModel.parts.browser; interactive: false
    }

    Button {
        id: backButton; label: qsTr("Back"); rotation: 0; x: parent.width - backButton.width - 6
        y: -backButton.height - 8; visible: Qt.platform.os !== "android"
    }

    Rectangle {
        id: photosShade; color: 'black'; width: parent.width; height: parent.height
        opacity: 0; visible: opacity != 0.0
    }

    ListView {
        anchors.fill: parent; model: albumVisualModel.parts.fullscreen; interactive: false
    }

    Item {
        id: foreground; anchors.fill: parent
    }

    ProgressBar {
        progress: mainWindow.downloadProgress; width: parent.width; height: 4
        anchors.bottom: parent.bottom; opacity: mainWindow.imageLoading; visible: opacity != 0.0
    }
}
