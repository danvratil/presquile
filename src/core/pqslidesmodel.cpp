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

#include "pqslidesmodel.h"
#include "pqslide.h"

#include <QStandardItem>
#include <QDebug>

PQSlidesModel::PQSlidesModel(QObject* parent)
    : QStandardItemModel(parent)
{

}

PQSlidesModel::~PQSlidesModel()
{

}

void PQSlidesModel::appendSlide(const PQSlide::Ptr &slide)
{
    QStandardItem *item = new QStandardItem;
    item->setData(QVariant::fromValue<PQSlide::Ptr>(slide), PQSlideRole);

    appendRow(item);
}

void PQSlidesModel::removeSlide(const PQSlide::Ptr& slide)
{
    int row = slideIndex(slide);
    if (row > -1) {
        removeRow(row);
    }
}

int PQSlidesModel::slideIndex(const PQSlide::Ptr& slide)
{
    for (int ii = 0; ii < rowCount(); ii++) {
        QModelIndex row = index(ii, 0);

        if (row.data(PQSlideRole).value<PQSlide::Ptr>() == slide) {
            return ii;
        }
    }

    return -1;
}

PQSlide::Ptr PQSlidesModel::slideAt(int row)
{
    QModelIndex i = index(row, 0);
    if (!i.isValid()) {
        return PQSlide::Ptr();
    }

    return i.data(PQSlideRole).value<PQSlide::Ptr>();
}

#include "pqslidesmodel.moc"
