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

#include "pqslidesmodeldelegate.h"
#include "pqslidedesigner.h"
#include "core/pqslide.h"
#include "core/pqslidesmodel.h"

#include <math.h>

#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QListView>
#include <QDeclarativeItem>
#include <QDeclarativeView>
#include <QDeclarativeEngine>

PQSlidesModelDelegate::PQSlidesModelDelegate(QListView *parent)
    : QStyledItemDelegate(parent)
    , mDesigner(0)
{
}

PQSlidesModelDelegate::~PQSlidesModelDelegate()
{
}

void PQSlidesModelDelegate::setDesigner(PQSlideDesigner* designer)
{
    mDesigner = designer;
}

void PQSlidesModelDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{

    PQSlide::Ptr slide = index.data(PQSlidesModel::PQSlideRole).value<PQSlide::Ptr>();
    if (slide.isNull()) {
        return;
    }

    painter->save();

    QDeclarativeItem *slideRoot = qobject_cast<QDeclarativeItem*>(slide->rootObject());
    QDeclarativeItem *slideRect = slideRoot->findChild<QDeclarativeItem*>(QLatin1String("slideRect"));
    QRect rect = QRect(slideRect->x(), slideRect->y(), slideRect->width(), slideRect->height());

    QSize itemSize = sizeHint(option, index);
    QRect targetRect = QRect(10, option.rect.y() + 10, itemSize.width() - 20, itemSize.height() - 20);

    if (option.state & QStyle::State_Selected) {
        QPen pen = painter->pen();
        painter->fillRect(option.rect, option.palette.highlight());

        int realWidth = floor(slideRect->width() * slideRect->scale());
        int realHeight = floor(slideRect->height() * slideRect->scale());
        int realX = floor((slideRoot->width() - realWidth) / 2);
        int realY = floor((slideRoot->height() - realHeight) / 2);

        mDesigner->render(painter, targetRect, QRect(realX, realY, realWidth, realHeight));
    } else {
        QDeclarativeView view;
        view.scene()->addItem(slideRoot);
        view.scene()->render(painter, targetRect, rect);
        view.scene()->removeItem(slideRoot);
    }

    painter->restore();
}

QSize PQSlidesModelDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    PQSlide::Ptr slide = index.data(PQSlidesModel::PQSlideRole).value<PQSlide::Ptr>();
    if (slide.isNull()) {
        return QStyledItemDelegate::sizeHint(option, index);
    }

    QObject *rootItem = slide->rootObject();
    QDeclarativeItem *slideRect = rootItem->findChild<QDeclarativeItem*>(QLatin1String("slideRect"));
    QListView *view = qobject_cast<QListView*>(parent());

    float ratio = (float) slideRect->width()/ (float) slideRect->height();
    QSize size = QSize(view->viewport()->width(), (float) view->width() / ratio);

    if (size != mLastSize) {
        mLastSize = size;
        //* Can't emit signal in const method, workaround it using queued connection */
        PQSlidesModelDelegate *delegate = const_cast<PQSlidesModelDelegate*>(this);
        QMetaObject::invokeMethod(delegate, "sizeHintChanged", Qt::QueuedConnection, Q_ARG(QModelIndex, index));
    }

    return size;
}

#include "pqslidesmodeldelegate.moc"
