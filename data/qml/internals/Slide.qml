/*
 * Copyright (C) 2012  Dan Vratil <dan@progdan.cz>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

import QtQuick 1.0

Item {
    id: root;
    objectName: "slideRoot";

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
}