import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls
import "../DashboardControls" as DashboardControls

Controls.Popup {
    id: popup
    closePolicy: Controls.Popup.CloseOnEscape | Controls.Popup.CloseOnPressOutsideParent

    Connections {
        target: display
        ignoreUnknownSignals: true
        onUpdateCommandStatus: {
            switch (command) {
            case Command.ArmDisarm:
                armDisarm.status = status;
                break;
            default:
                break;
            }
        }
    }

    DashboardControls.DelayCommandButton {
        id: armDisarm
        text: vehicle.armed ? qsTr("DISARM") : qsTr("ARM")
        args: [ !vehicle.armed ]
        command: Command.ArmDisarm
        implicitWidth: sizings.controlBaseSize * 3
    }
}


