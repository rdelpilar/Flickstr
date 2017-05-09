import QtQuick 2.2

Flipable {
   id: flipable

   property alias frontLabel: frontButton.label
   property alias backLabel: backButton.label

   property int angle: 0
   property int randomAngle: 0
   property bool flipped: false

   signal frontClicked
   signal backClicked
   signal tagChanged(string tag)

   front: EditableButton {
       id: frontButton
       label: qsTr("Enter Tag")

       //rotation: flipable.randomAngle
       anchors {
           centerIn: parent
           verticalCenterOffset: -20
       }
       onClicked: flipable.frontClicked()
       onLabelChanged: flipable.tagChanged(label)
   }

   back: Button {
       id: backButton
       tint: "red"
       rotation: flipable.randomAngle
       anchors {
           centerIn: parent
           verticalCenterOffset: -20
       }
       onClicked: flipable.backClicked()
   }

   transform: Rotation {
       origin.x: flipable.width / 2
       origin.y: flipable.height / 2
       angle: flipable.angle
   }

   states: State {
       name: "back"
       when: flipable.flipped
       PropertyChanges {
           target: flipable
           angle: 180
       }
   }

   transitions: Transition {
       ParallelAnimation {
           NumberAnimation {
               properties: "angle"
               duration: 400
           }
           SequentialAnimation {
               NumberAnimation {
                   target: flipable
                   property: "scale"
                   to: 0.8
                   duration: 200
               }
               NumberAnimation {
                   target: flipable
                   property: "scale"
                   to: 1.0
                   duration: 200
               }
           }
       }
   }
}
