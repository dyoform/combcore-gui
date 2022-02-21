import QtQuick 2.15
import QtQuick.Controls 2.12

import combcore 1.0
import combcore.gui 1.0

import "../"
import "../style"

Rectangle {
    readonly property real buttonSize: 40
    property CameraControls control: GUI.cameraControls
    property real gizmoSize: 60
    radius: 5
    width: 250
    height: buttonSize
    anchors.topMargin: {5 + (gizmoSize-buttonSize)/2}
    color: Constants.structureColor

    Row {
        id: controlsRow
        property real space: {(parent.width-(buttonSize*3)-gizmoSize)/5}
        spacing: space
        leftPadding: space
        rightPadding: space

        SButton {
            icon.source: "qrc:/images/reset_camera_icon.svg"
            display: AbstractButton.IconOnly
            radius: 5
            width: buttonSize
            height: buttonSize
            onPressed: control.resetCamera()
        }

        Row {
            id: exclusiveButtons
            spacing: controlsRow.space
            SButton {
                icon.source: "qrc:/images/ortho_icon.svg"
                display: AbstractButton.IconOnly
                checkable: true
                radius: 5
                width: buttonSize
                height: buttonSize
                checked: control.activeProjection === CameraControls.PROJECTION_ORTHO
                onPressed: control.activeProjection = CameraControls.PROJECTION_ORTHO
            }
            SButton {
                icon.source: "qrc:/images/perspective_icon.svg"
                display: AbstractButton.IconOnly
                checkable: true
                radius: 5
                width: buttonSize
                height: buttonSize
                checked: control.activeProjection === CameraControls.PROJECTION_PERSPECTIVE
                onPressed: control.activeProjection = CameraControls.PROJECTION_PERSPECTIVE
            }
        }

        ButtonGroup {
            buttons: exclusiveButtons.children
        }

        Rectangle {
            radius: {gizmoSize/2}
            y: {-(gizmoSize-buttonSize)/2}
            width: gizmoSize
            height: gizmoSize
            color: Constants.structureColor
        }
    }
}
