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
#include "core/pqqmlloader.h"
#include "editors/propertyeditor.h"

#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QStringBuilder>
#include <QDeclarativeItem>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QPointer>
#include <QMessageBox>

PQSlideDesigner::PQSlideDesigner(QWidget* parent)
    : QDeclarativeView(parent)
    , mCurrentSlide(0)
{
    setResizeMode(SizeRootObjectToView);
    setAcceptDrops(true);
    engine()->rootContext()->setContextProperty(QLatin1String("_inEditMode"), true);
}

PQSlideDesigner::~PQSlideDesigner()
{

}

void PQSlideDesigner::setSlide(const PQSlide::Ptr& slide)
{
    if (mCurrentSlide == slide) {
        return;
    }

    if (mCurrentSlide) {
        scene()->removeItem(qobject_cast<QGraphicsItem*>(mCurrentSlide->rootObject()));
    }

    mCurrentSlide = slide;
    if (slide) {
        setRootObject(slide->rootObject());
    }
}

PQSlide::Ptr PQSlideDesigner::slide() const
{
    return mCurrentSlide;
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
    QDeclarativeItem *slide = slideRect();
    QDeclarativeItem *root = slideRoot();
    if (!slide || !root) {
        event->ignore();
        return;
    }

    /* We must convert the real dimensions to the visual ones - i.e. apply scale */
    const int width = slide->width() * slide->scale();
    const int height = slide->height() * slide->scale();
    const int x = (root->width() - width) / 2;
    const int y = (root->height() - height) / 2;
    const QRect slideRect(x, y, width, height);

    if (slideRect.contains(event->pos(), true)) {
        event->accept();
        return;
    }

    event->ignore();
}

void PQSlideDesigner::dropEvent(QDropEvent* event)
{
    QString type = event->mimeData()->text();

    if (!type.startsWith(QLatin1String("Component/"))) {
        event->ignore();
        return;
    }

    QString comp = type.remove(QLatin1String("Component/"));

    PQQmlLoader *manager = PQQmlLoader::instance();
    QDeclarativeItem *item = manager->componentInstance(engine(), comp);
    if (!item) {
        qWarning() << "Failed to create an instance of" << comp;
        return;
    }

    QDeclarativeItem *slideContainer = slideChildrenContainer();
    QDeclarativeItem *rect = slideRect();
    QDeclarativeItem *root = slideRoot();
    if (!slideContainer || !root) {
        return;
    }

    item->setParentItem(slideContainer);

    /* Transform to current visual coordinates, which can be different from the
     * real ones thanks to scaling of the slide rect */
    const int rootX = (root->width() - (rect->width() * rect->scale())) / 2;
    const int rootY = (root->height() - (rect->height() * rect->scale())) / 2;
    const QPointF newPos(event->pos().x() - rootX, event->pos().y() - rootY);
    item->setPos(newPos);

    connect(item, SIGNAL(focusChanged(bool)), this, SLOT(slotItemFocusChanged(bool)));
    item->setProperty("focus", true);

    connect(item, SIGNAL(doubleClicked()), this, SLOT(slotItemDoubleClicked()));

    event->acceptProposedAction();
}

void PQSlideDesigner::keyReleaseEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Delete) {
        QDeclarativeItem *slideContainer = slideChildrenContainer();
        if (!slideContainer) {
            qWarning() << "Failed to locate slide container element";
            return;
        }

        QListIterator<QGraphicsItem*> iter(slideContainer->childItems());
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

void PQSlideDesigner::slotItemDoubleClicked()
{
    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(sender());
    if (!item) {
        return;
    }

    QString editProperty = item->property("_PQDoubleClickEdit").toString();
    if (editProperty.isEmpty()) {
        return;
    }

    QPointer<PropertyEditor> editor = new PropertyEditor(item, editProperty, this);
    editor->exec();

    delete editor;
}


QDeclarativeItem* PQSlideDesigner::slideRoot() const
{
    return qobject_cast<QDeclarativeItem*>(rootObject());
}

QDeclarativeItem* PQSlideDesigner::slideRect() const
{
    return rootObject()->findChild<QDeclarativeItem*>(QLatin1String("slideRect"));
}

QDeclarativeItem* PQSlideDesigner::slideChildrenContainer() const
{
    return rootObject()->findChild<QDeclarativeItem*>(QLatin1String("slideRootFocusScope"));
}



#include "pqslidedesigner.moc"
