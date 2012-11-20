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

#include "pqslidedesigner.h"
#include "coreutils.h"
#include "qml/pqqmlmanager.h"

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QStringBuilder>
#include <QDeclarativeItem>
#include <QDeclarativeEngine>
#include <QMessageBox>

PQSlideDesigner::PQSlideDesigner(QWidget* parent)
    : QDeclarativeView(parent)
{
    setResizeMode(SizeRootObjectToView);
    setAcceptDrops(true);

    setSource(QUrl(CoreUtils::resourcePath() % QLatin1String("/qml/internals/Slide.qml")));
}

PQSlideDesigner::~PQSlideDesigner()
{

}

void PQSlideDesigner::dragEnterEvent(QDragEnterEvent* event)
{
    if (!event->mimeData()->text().startsWith(QLatin1String("Component/"))) {
	event->ignore();
	return;
    }

    event->acceptProposedAction();
}

void PQSlideDesigner::dragMoveEvent(QDragMoveEvent* event)
{
    /* Always allow dragged item to be moved around */
    event->accept();
}

void PQSlideDesigner::dropEvent(QDropEvent* event)
{
    QString type = event->mimeData()->text();

    if (!type.startsWith(QLatin1String("Component/"))) {
	event->ignore();
	return;
    }

    QString comp = type.remove(QLatin1String("Component/"));

    PQQMLManager *manager = PQQMLManager::instance();
    QDeclarativeItem *item = manager->componentInstance(engine(), comp);
    if (!item) {
	qWarning() << "Failed to create an instance of" << comp;
	return;
    }

    /* FIXME: Be more generic here */
    QDeclarativeItem *slide = slideRoot();
    if (!slide) {
	qWarning() << "Failed to locate slide root element";
	return;
    }

    item->setParentItem(slide);
    item->setProperty("x", event->pos().x() - slide->x());
    item->setProperty("y", event->pos().y() - slide->y());
    item->setProperty("focus", true);
    connect(item, SIGNAL(focusChanged(bool)), this, SLOT(slotItemFocusChanged(bool)));

    event->acceptProposedAction();
}

void PQSlideDesigner::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete) {
	QDeclarativeItem *slide = slideRoot();
	if (!slide) {
	    qWarning() << "Failed to locate slide root element";
	    return;
	}

	QListIterator<QGraphicsItem*> iter(slide->childItems());
	while (iter.hasNext()) {
	    QDeclarativeItem *dItem = qobject_cast<QDeclarativeItem*>(iter.next());
	    if (dItem && dItem->hasFocus()) {
		qDebug() << "Deleting" << dItem;
		dItem->deleteLater();

		/* Move focus */
		if (iter.hasPrevious()) {
		    QObject *prev = qobject_cast<QObject*>(iter.peekPrevious());
		    qDebug() << "Moving focus to" << qobject_cast<QDeclarativeItem*>(prev);
		    prev->setProperty("focus", true);
		} else {
		    qDebug() << "Unsetting focus";
		    Q_EMIT focusedItemChanged(0);
		}
	    }
	}

	return;
    }

    QGraphicsView::keyReleaseEvent(event);
}

void PQSlideDesigner::slotItemFocusChanged(bool hasFocus)
{
    if (hasFocus) {
	qDebug() << "Focused item changed to" << qobject_cast<QDeclarativeItem*>(sender());
	Q_EMIT focusedItemChanged(sender());
    }
}

QDeclarativeItem* PQSlideDesigner::slideRoot() const
{
    return rootObject()->findChild<QDeclarativeItem*>(QLatin1String("slideRootFocusScope"));
}



#include "pqslidedesigner.moc"