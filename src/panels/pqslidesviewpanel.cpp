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

#include "pqslidesviewpanel.h"
#include "../mainwindow.h"
#include "../pqslidesmodeldelegate.h"
#include "../pqslidesmodel.h"

#include <QListWidget>
#include <QVBoxLayout>
#include <QTimer>

PQSlidesViewPanel::PQSlidesViewPanel(MainWindow* parent, Qt::WindowFlags flags)
  : QDockWidget(tr("Slides"), parent, flags)
{
    mSlidesListwidget = new QListView(this);
    mSlidesListwidget->setModel(parent->slidesModel());
    mSlidesListwidget->setDragDropMode(QAbstractItemView::InternalMove);
    mSlidesListwidget->setDragEnabled(false);
    mSlidesListwidget->setSelectionMode(QAbstractItemView::SingleSelection);
    mSlidesListwidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mSlidesListwidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mSlidesListwidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    mSlidesListwidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mSlidesListwidget->setUniformItemSizes(true);
    mSlidesListwidget->setSelectionRectVisible(true);

    PQSlidesModelDelegate *delegate = new PQSlidesModelDelegate(mSlidesListwidget);
    delegate->setDesigner(parent->slideDesigner());
    mSlidesListwidget->setItemDelegate(delegate);

    connect(mSlidesListwidget, SIGNAL(activated(QModelIndex)),
            this, SLOT(currentItemChanged(QModelIndex)));

    setWidget(mSlidesListwidget);

    mRedrawTimer = new QTimer(this);
    mRedrawTimer->setInterval(600);
    connect(mRedrawTimer, SIGNAL(timeout()), this, SLOT(updateItem()));
    mRedrawTimer->start();
}

PQSlidesViewPanel::~PQSlidesViewPanel()
{

}

void PQSlidesViewPanel::currentItemChanged(const QModelIndex &index)
{
    PQSlide::Ptr slide = index.data(PQSlidesModel::PQSlideRole).value<PQSlide::Ptr>();

    Q_EMIT slideActivated(slide);
}

void PQSlidesViewPanel::updateItem()
{
    if (!mSlidesListwidget->currentIndex().isValid()) {
        return;
    }

    mSlidesListwidget->update(mSlidesListwidget->currentIndex());
}


#include "pqslidesviewpanel.moc"