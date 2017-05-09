import QtQuick 2.2
import QtQuick.Controls 2.0
import QtQml.Models 2.1
import ControllerLib 1.0

Component {
    id: albumDelegate

    Package {
        Item {
            Package.name: 'browser'
            GridView {
                id: photosGridView;
                model: visualModel.parts.grid; width: mainWindow.width; height: mainWindow.height - 21
                x: 0; y: 21; cellWidth: 160; cellHeight: 153; interactive: false
                onCurrentIndexChanged: photosListView.positionViewAtIndex(currentIndex, ListView.Contain)
            }
        }

        Item {
            Package.name: 'fullscreen'
            ListView {
                id: photosListView; model: visualModel.parts.list; orientation: Qt.Horizontal
                width: mainWindow.width; height: mainWindow.height; interactive: false
                onCurrentIndexChanged: photosGridView.positionViewAtIndex(currentIndex, GridView.Contain)
                highlightRangeMode: ListView.StrictlyEnforceRange; snapMode: ListView.SnapOneItem
            }
        }

        Item {
            property int listModelIndex: index
            Package.name: 'album'
            id: albumWrapper; width: 210; height: 220

            // Entry point to C++
            DelegateModel {
                id: visualModel; model: RssModelRole; delegate: PhotoDelegate { rssListModelIndex: albumWrapper.listModelIndex}
            }

            BusyIndicator {
                id: busyIndicator
                anchors { centerIn: parent; verticalCenterOffset: -20 }
                //on: RssModelRole.status != RssModelRole.Ready // enabling will call RssModel.data additional 2x
                // on: rssModel.status != XmlListModel.Ready
            }

            // BorderImage added: 1/6/2017
//            BorderImage {
//                anchors {
//                    fill: border
//                    leftMargin: -6; topMargin: -6; rightMargin: -8; bottomMargin: -8
//                }
//                anchors.centerIn: parent; antialiasing: true; anchors.verticalCenterOffset: -18 // added entire line
//                width: 160; height: 100; visible: true // added entire line
//                source: 'images/box-shadow.png'
//                border.left: 10; border.top: 10; border.right: 10; border.bottom: 10
//            }

//            // Rectangle added: 1/6/2017
//            Rectangle {
//                id: placeHolder
//                color: 'white'; anchors.centerIn: parent; antialiasing: true; anchors.verticalCenterOffset: -20
//                width: 140; height: 80; visible: true
//                Rectangle {
//                    color: "#878787"; antialiasing: true
//                    anchors { fill: parent; topMargin: 3; bottomMargin: 3; leftMargin: 3; rightMargin: 3 }
//                }
//            }

//            // Rectangle added: 1/6/2017
//            Rectangle {
//                id: border; color: 'white'; anchors.centerIn: parent; antialiasing: true; anchors.verticalCenterOffset: -20
//                width: 140; height: 80
//                visible: !placeHolder.visible
//            }

            PathView {
                id: photosPathView
                model: visualModel.parts.stack; pathItemCount: 5
                visible: !busyIndicator.visible; //<<--- PUT BACK
                anchors.centerIn: parent; anchors.verticalCenterOffset: -30
                path: Path {
                    PathAttribute { name: 'z'; value: 9999.0 }
                    PathLine { x: 1; y: 1 }
                    PathAttribute { name: 'z'; value: 0.0 }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: mainWindow.editMode ? photosModel.remove(index) : albumWrapper.state = 'inGrid'
            }

//            ProgressBar {
//                id: progressBar;
//                visible: false
//                width: 100; //anchors.centerIn: parent; anchors.verticalCenterOffset: 0
//                anchors.centerIn: border
//                Connections {
//                    target: DownloadProgressHandler
//                    onVisibleChanged: progressBar.visible = DownloadProgressHandler.getVisibleState(index)
//                    onValueChanged: progressBar.value = DownloadProgressHandler.getValue(index)
//                }
//            }

            Tag {
                anchors { horizontalCenter: parent.horizontalCenter; bottom: parent.bottom; bottomMargin: 10 }
                /*frontLabel: qsTr("");*/ backLabel: qsTr("Back"); flipped: mainWindow.editMode
                onTagChanged: {
                    Controller.setTag(index, frontLabel);
                }
                onBackClicked: if(mainWindow.editMode) photosModel.remove(index)
            }

            states: [
                State {
                    name: 'inGrid'
                    PropertyChanges { target: photosGridView; interactive: true }
                    PropertyChanges { target: albumsShade; opacity: 1 }
                    PropertyChanges { target: backButton; onClicked: albumWrapper.state = ''; y: 6 }
                },
                State {
                    name: 'fullscreen'; extend: 'inGrid'
                    PropertyChanges { target: photosGridView; interactive: false }
                    PropertyChanges { target: photosListView; interactive: true }
                    PropertyChanges { target: photosShade; opacity: 1 }
                    PropertyChanges { target: backButton; y: -backButton.height - 8 }
                }
            ]

            GridView.onAdd: NumberAnimation {
                target: albumWrapper; properties: "scale"; from: 0.0; to: 1.0; easing.type: Easing.OutQuad
            }

            GridView.onRemove: SequentialAnimation {
                PropertyAction { target: albumWrapper; property: "GridView.delayRemove"; value: true }
                NumberAnimation { target: albumWrapper; property: "scale"; from: 1.0; to: 0.0; easing.type: Easing.OutQuad }
                PropertyAction { target: albumWrapper; property: "GridView.delayRemove"; value: false }
            }

            transitions: [
                Transition {
                    from: '*'; to: 'inGrid'
                    SequentialAnimation {
                        NumberAnimation { properties: 'opacity'; duration: 250 }
                        PauseAnimation { duration: 350 }
                        NumberAnimation { target: backButton; properties: "y"; duration: 200; easing.type: Easing.OutQuad }
                    }
                },
                Transition {
                    from: 'inGrid'; to: '*'
                    NumberAnimation { properties: "y,opacity"; easing.type: Easing.OutQuad; duration: 300 }
                }
            ]
        }
    }
}
