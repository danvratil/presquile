import QtQuick 1.0

Item {
    id: root;

    property bool isEditable: false;
    property Item contentView;
    property Item handle: handleInst;

    /*
    Rectangle {
	id: contentEditor;
	border {
	    color: "black";
	    width: 1;
	}

	visible: false;

	property alias text: textEdit.text;

	TextEdit {
	    id: textEdit;
	    anchors {
		fill: parent;
		margins: 5;
	    }
	    smooth: true;
	    textFormat: TextEdit.RichText;
	    selectByMouse: true;
	    wrapMode: TextEdit.Wrap;
	}

	anchors.top: root.top;
	anchors.left: root.left;
	anchors.right: handle.horizontalCenter;
	anchors.bottom: handle.verticalCenter;
    }
    */

    Rectangle {
	id: handleInst;
	width: 10;
	height: 10;
	color: "blue";
	/* FIXME: Hack! */
	z: 100000000;

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
	width: contentView.width;
	height: contentView.height;

	drag {
	    target: root;
	    axis: Drag.XandYAxis;
	    minimumX: 0;
	    minimumY: 0;
	    maximumX: root.parent.width - contentView.width - 5;
	    maximumY: root.parent.height - contentView.height - 5;
	}

	onDoubleClicked: {
	    root.isEditable = true;
	}

	onPressed: {
	    root.focus = true;
	}
    }

    onIsEditableChanged: {
	if (contentView._PQEditable == false) {
	    return;
	}

	contentView.visible = !isEditable;
	contentEditor.visible = isEditable;
	moveMouseMarea.enabled = !isEditable;

	contentEditor.text = contentView.text;
    }

    onFocusChanged: {
	handleInst.visible = root.focus;
    }

    Component.onCompleted: {
	handleInst.x = _PQInitialWidth;
	handleInst.y = _PQInitialHeight;
    }
}