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

PQResizable {

    property string		_PQDisplayName:		qsTr("Rectangle");
    property string		_PQDescription:		qsTr("A rectangle");
    property int 		_PQInitialWidth:	200;
    property int 		_PQInitialHeight:	200;
    property bool 		_PQEditable:		false;
    property variant		_PQProperties:		[ "color",
							  "gradient",
							  "height",
							  "opacity",
							  "radius",
							  "rotation",
							  "scale",
							  "smooth",
							  "width",
							  "x",
							  "y",
							  "z" ];

    property alias color: rect.color;
    property alias gradient: rect.gradient;
    property alias radius: rect.radius;
    property alias smooth: rect.smooth;

    contentView: rect;

    Rectangle {
	id: rect;
	color: "red";

	anchors.top: parent.top;
	anchors.left: parent.left;
	anchors.right: parent.handle.horizontalCenter;
	anchors.bottom: parent.handle.verticalCenter;
    }
}