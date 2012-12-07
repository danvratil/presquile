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
#include "pqslide.h"
#include "pqslidesmodel.h"

#include <QPainter>
#include <QGraphicsView>

PQSlidesModelDelegate::PQSlidesModelDelegate(QWidget *parent)
    : QStyledItemDelegate(parent)
{
}

PQSlidesModelDelegate::~PQSlidesModelDelegate()
{
}

void PQSlidesModelDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    PQSlide::Ptr slide = index.data(PQSlidesModel::PQSlideRole).value<PQSlide::Ptr>();
    if (slide.isNull()) {
        return;
    }

    QGraphicsScene *scene = slide->scene();

    QRectF targetRect(10, 10, option.rect.width() - 20, option.rect.height() -20);
    scene->render(painter, targetRect);
}

QSize PQSlidesModelDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    PQSlide::Ptr slide = index.data(PQSlidesModel::PQSlideRole).value<PQSlide::Ptr>();
    if (slide.isNull()) {
        return QStyledItemDelegate::sizeHint(option, index);
    }

    QGraphicsScene *scene = slide->scene();

    QWidget *view = qobject_cast<QWidget*>(parent());

    float ratio = (float) scene->width() / (float) scene->height();
    return QSize(view->width() - 10, (float) view->width() / ratio);
}





#include "pqslidesmodeldelegate.moc"
