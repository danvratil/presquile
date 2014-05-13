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
import presquile 1.0

PQResizable {

    property string     _PQDisplayName:         qsTr("Text");
    property string     _PQDescription:         qsTr("Display a HTML-formatted text");
    property int        _PQInitialWidth:        200;
    property int        _PQInitialHeight:       40;
    property string     _PQDoubleClickEdit:     "text";
    property variant    _PQProperties:          [ "color",
                                                  "elide",
                                                  "height",
                                                  "opacity",
                                                  //"lineHeight",
                                                  //"lineHeightMode",
                                                  "rotation",
                                                  "scale",
                                                  "smooth",
                                                  "text",
                                                  "verticalAlignment",
                                                  "width",
                                                  "wrapMode",
                                                  "x",
                                                  "y",
                                                  "z" ];

    property alias color: text.color;
    property alias elide: text.elide;
    /* FIXME: QtQuick 1.1 */
    //property alias lineHeight: text.lineHeight;
    //property alias lineHeightMode: text.lineHeightMode;
    property alias smooth: text.smooth;
    property alias text: text.text;
    property alias verticalAlignment: text.verticalAlignment;
    property alias wrapMode: text.wrapMode;

    resizableItem: text;

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

    Text {
        id: text;
        z: 1;

        wrapMode: Text.Wrap;
        clip: true;

        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.handle.horizontalCenter;
        anchors.bottom: parent.handle.verticalCenter;
    }

    PQItemFrame {
        id: frame;
        z: 0;

        anchors.fill: text;
    }
}
