import QtQuick 1.0
import presquile 1.0

PQBaseItem {
    id: root;

    property Item resizableItem;
    property Item handle: handleInst;

    signal doubleClicked();


    Rectangle {
        id: handleInst;
        width: 10;
        height: 10;
        color: "blue";
        /* FIXME: Hack! */
        z: 100000000;

       /* FIXME: handleInst should not change scale */

        MouseArea {
            id: handleMouseArea;
            anchors.fill: parent;
            drag {
                target: handleInst;
                axis: Drag.XandYAxis;
                minimumX: 5;
                maximumX: root.parent.width - root.x - root.width - 5;
                minimumY: 5;
                maximumY: root.parent.height - root.y - root.height - 5;
            }
        }
    }

    MouseArea {
        id: moveMouseMarea;
        x: 0;
        y: 0;
        width: resizableItem.width;
        height: resizableItem.height;

        drag {
            target: root;
            axis: Drag.XandYAxis;
            minimumX: 0;
            minimumY: 0;
            maximumX: root.parent.width - resizableItem.width - 5;
            maximumY: root.parent.height - resizableItem.height - 5;
        }

        onDoubleClicked: {
            root.doubleClicked();
        }

        onPressed: {
            root.focus = true;
        }
    }

    onFocusChanged: {
        handleInst.visible = root.focus;
    }

    Component.onCompleted: {
        handleInst.x = _PQInitialWidth;
        handleInst.y = _PQInitialHeight;
    }
}
