import QtQuick 2.7

Package {

    id: packageId
    property int rssListModelIndex

    Item { id: stackItem; Package.name: 'stack'; width: 160; height: 153; z: stackItem.PathView.z }
    Item { id: listItem; Package.name: 'list'; width: mainWindow.width + 40; height: 153 }
    Item { id: gridItem; Package.name: 'grid'; width: 160; height: 153 }

    Item {
        width: 160
        height: 153

        Item {
            id: photoWrapper

            property double randomAngle: 0
            property double randomAngle2: 0

            x: 0; y: 0; width: 140; height: 133;
            z: stackItem.PathView.z; rotation: photoWrapper.randomAngle

            BorderImage {
                anchors {
                    fill: originalImage.status == Image.Ready ? border : placeHolder
                    leftMargin: -6; topMargin: -6; rightMargin: -8; bottomMargin: -8
                }
                source: 'images/box-shadow.png'
                border.left: 10; border.top: 10; border.right: 10; border.bottom: 10
            }

            Rectangle {
                id: placeHolder

                function calculateScale(width, height, cellSize) {
                    //console.log("Before: ---- width: " + width + ", height: " + height + ", cellSize: " + cellSize)
                    var widthScale = (cellSize * 1.0) / width
                    var heightScale = (cellSize * 1.0) / height
                    var scale = 0

                    if (widthScale <= heightScale) {
                        scale = widthScale;
                    } else if (heightScale < widthScale) {
                        scale = heightScale;
                    }
                    //console.log("After: ---- scale: " + scale)
                    return scale;
                }

                property int w: PhotoWidthRole
                property int h: PhotoHeightRole
                property double s: calculateScale(w, h, photoWrapper.width)

//                property int w: photoWrapper.width
//                property int h: photoWrapper.height

                color: 'white'; anchors.centerIn: parent; antialiasing: true
                width: w * s; height: h * s; visible: originalImage.status != Image.Ready
                Rectangle {
                    color: "#878787"; antialiasing: true
                    anchors { fill: parent; topMargin: 3; bottomMargin: 3; leftMargin: 3; rightMargin: 3 }
                }
                Component.onCompleted: {}
            }

            Rectangle {
                id: border; color: 'white'; anchors.centerIn: parent; antialiasing: true
                width: originalImage.paintedWidth + 6; height: originalImage.paintedHeight + 6
                visible: !placeHolder.visible
            }

            BusyIndicator {
                anchors.centerIn: parent; on: originalImage.status != Image.Ready
            }

            Image {
                id: originalImage; antialiasing: true
                source: index == -1
                        ? ""
                        : PhotoThumbnailRole
                cache: true
                sourceSize.width: photoWrapper.width
                sourceSize.height: photoWrapper.height
                fillMode: Image.PreserveAspectFit
                width: photoWrapper.width; height: photoWrapper.height
                onStatusChanged: {}
                Component.onCompleted: {}
            }

            Image {
                id: hqImage; antialiasing: true; opacity: 1
                source: ""
                visible: false;
                cache: false
                sourceSize.width: PhotoWidthRole
                sourceSize.height: PhotoHeightRole
                fillMode: Image.PreserveAspectFit;
                width: photoWrapper.width; height: photoWrapper.height
                Component.onCompleted: {}
                onStatusChanged: {
//                    console.log("Status changed")
//                    test1.to = 22
//                    animator.start()
                }


//                THE PROBLEM HERE IS THE IMAGE IS CUT OFF FROM THE BOTTOM WHEN DISPLAYED IN LISTVIEW
//                ALSO NEED TO FIGURE OUT A WAY TO MAKE THE BACK BUTTON DROP FROM TOP WHILE BROWSING LIST VIEW
//                states: State {
//                    when: hqImage.status == Image.Ready
//                    PropertyChanges { target: backButton; y: 15 }
//                }

//                transitions: Transition {
//                    SequentialAnimation {
//                        NumberAnimation { properties: 'opacity'; duration: 250 }
//                        PauseAnimation { duration: 350 }
//                        NumberAnimation { target: backButton; properties: "y"; duration: 200; easing.type: Easing.OutQuad }
//                    }
//                }

            }

            Row {
                spacing: 40;
                id: rowId
                anchors.bottom: parent.bottom; anchors.bottomMargin: -50
                anchors.horizontalCenter: parent.horizontalCenter

                Button {
                    id: deleteButton; label: qsTr("Delete");
                    anchors.verticalCenter: parent.verticalCenter
                    visible: false
                    onClicked: console.log("deleteButton clicked")
                }

                Button {
                    id: newButton; label: qsTr("New");
                    anchors.verticalCenter: parent.verticalCenter
                    visible: false
                    onClicked: {
                        console.log("newButton clicked")
                    }
                }

                Button {
                    id: returnButton; label: qsTr("Return");
                    anchors.verticalCenter: parent.verticalCenter
                    visible: false
                    onClicked: {
                        gridItem.GridView.view.currentIndex = index
                        albumWrapper.state = 'ingrid'
                        console.log("returnButton clicked")
                    }
                }
            }

            Binding {
                target: mainWindow; property: "downloadProgress"
                value: hqImage.progress; when: listItem.ListView.isCurrentItem
            }

            Binding {
                target: mainWindow; property: "imageLoading"
                value: (hqImage.status == Image.Loading) ? 1 : 0; when: listItem.ListView.isCurrentItem
            }

            MouseArea {
                width: originalImage.paintedWidth; height: originalImage.paintedHeight// -40
                anchors.centerIn: originalImage
                onClicked: {
                    if(albumWrapper.state == 'inGrid') {
                        gridItem.GridView.view.currentIndex = index
                        albumWrapper.state = 'fullscreen'
                    } else {
                        console.log("Mouse clicked for mouse area photoWrapper")
                    }
                }
            }

            states: [
                State {
                    name: 'stacked'; when: albumWrapper.state == ''
                    ParentChange { target: photoWrapper; parent: stackItem; x: 10; y: 10 }
                    PropertyChanges { target: photoWrapper; opacity: stackItem.PathView.onPath ? 1.0 : 0.0 }
                },
                State {
                    name: 'inGrid'; when: albumWrapper.state == 'inGrid'
                    ParentChange { target: photoWrapper; parent: gridItem; x: 10; y: 10; /*rotation: photoWrapper.randomAngle2*/ }
                },
                State {
                    name: 'fullscreen'; when: albumWrapper.state == 'fullscreen'
                    ParentChange {
//                        target: photoWrapper; parent: listItem; x: 0; y: 0; rotation: 0
//                        width: mainWindow.width; height: mainWindow.height
                        target: photoWrapper; parent: listItem; x: 0; y: 0; rotation: 0
                        width: mainWindow.width; height: mainWindow.height - 120
                    }

                    PropertyChanges { target: border; opacity: 0 }
                    PropertyChanges { target: deleteButton; visible: true; }
                    PropertyChanges { target: newButton; visible: true }
                    PropertyChanges { target: returnButton; visible: true }
                    PropertyChanges { target: hqImage; source: listItem.ListView.isCurrentItem
                                                               ? PhotoHighQualityRole
                                                               : ""; visible: true }
                }
            ]

            transitions: [
                Transition {
                    from: 'stacked'; to: 'inGrid'
                    SequentialAnimation {
                        PauseAnimation { duration: index == -1 ? 0 : (10 * index) }
                        ParentAnimation {
                            target: photoWrapper; via: foreground
                            NumberAnimation { target: photoWrapper; properties: 'x,y,rotation,opacity'; duration: 600; easing.type: 'OutQuart' }
                        }
                    }
                },
                Transition {
                    from: 'inGrid'; to: 'stacked'
                    ParentAnimation {
                        target: photoWrapper; via: foreground
                        NumberAnimation { properties: 'x,y,rotation,opacity'; duration: 600; easing.type: 'OutQuart' }
                    }
                },
                Transition {
                    from: 'inGrid'; to: 'fullscreen'
                    SequentialAnimation {
                        PauseAnimation { duration: gridItem.GridView.isCurrentItem ? 0 : 600 }
                        ParentAnimation {
                            target: photoWrapper
                            via: foreground
                            NumberAnimation {
                                targets: [photoWrapper, border]; properties: 'x,y,width,height,opacity,rotation'
                                duration: gridItem.GridView.isCurrentItem ? 600 : 1; easing.type: 'OutQuart'
                            }
                        }
                    }
                },
                Transition {
                    from: 'fullscreen'; to: 'inGrid'
                    ParentAnimation {
                        target: photoWrapper; via: foreground
                        NumberAnimation {
                            targets: [photoWrapper, border]; properties: 'x,y,width,height,rotation,opacity'
                            duration: gridItem.GridView.isCurrentItem ? 600 : 1; easing.type: 'OutQuart'
                        }
                    }
                }
            ]
        }
    }
}
