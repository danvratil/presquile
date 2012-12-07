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
import Presquile 1.0

PQResizable {

    property string		_PQDisplayName:		qsTr("Image");
    property string		_PQDescription:		qsTr("An image");
    property int 		_PQInitialWidth:	200;
    property int 		_PQInitialHeight:	200;
    property string 		_PQDoubleClickEdit:	"source";
    property variant		_PQProperties:		[ "height",
							  "fillMode",
							  "opacity",
							  "rotation",
							  "scale",
							  "smooth",
							  "source",
							  "width",
							  "x",
							  "y",
							  "z" ];

    property alias fillMode: img.fillMode;
    property alias source: img.source;
    property alias smooth: img.smooth;

    contentView: img;

    transform: [
	Translate {
	    x: 0;
	    y: 0;
	},
	Rotation {
	    angle: 0;
	    axis {
		x: 0;
		y: 0;
		z: 0;
	    }
	    origin {
		x: 0;
		y: 0;
	    }
	},
	Scale {
	    xScale: 1.0;
	    yScale: 1.0;
	    origin {
		x: 0;
		y: 0;
	    }
	}
    ]

    Image {
	id: img;
	sourceSize {
	    width: 800;
	    height: 600;
	}

	/* Display an border until an image is assigned */
	PQItemFrame {
	    id: borderRect;
	    anchors.fill: parent;
	    visible: (parent.source == "");
	}

	anchors.top: parent.top;
	anchors.left: parent.left;
	anchors.right: parent.handle.horizontalCenter;
	anchors.bottom: parent.handle.verticalCenter;
    }
}