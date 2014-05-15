/** PQSlide -- One slide in Presquile presentation
  * Copyright (C) 2014 Jan Stanek <khardix@gmail.com>
  * 
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  * 
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  * 
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */ 
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
