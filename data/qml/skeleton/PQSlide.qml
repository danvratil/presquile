// QML class representing one presentation slide

import QtQuick 1.0

Item {
    id: root;
    objectName: "slideRoot";

    anchors.fill: parent;

    SystemPalette {
        id: palette;
    }

    Rectangle {
        id: slideRect;
        objectName: "slideRect";

        width: 800;
        height: 600;
        radius: 10;
        focus: true;

        anchors.centerIn: parent;

        color: palette.light;

        FocusScope {
            id: focusScope;
            objectName: "slideRootFocusScope";

            anchors.fill: parent;
        }

        function updateScale() {
            /* "Real" size (including margin) is 880x680.
            * Scale the slideRectangle so that it always fits into root with
            * the margin
            * TODO: The margin should be scaled as well - the smaller the scale,
            * the smaller margin */

            slideRect.scale = Math.min(root.width / 880, root.height / 680);
        }
    }

    onHeightChanged: slideRect.updateScale();
    onWidthChanged: slideRect.updateScale();

    Component.onCompleted: {
      /**
       * Reparenting. First child of every slide is slideRect, all others should
       * be children of focusScope (visible slide area)
       */
      while (children.length > 1)
      {
        if (children[1].objectName.lastIndexOf('slideRect', 0) != 0) // not slideRect
          children[1].parent = focusScope;
      }
    }
}
