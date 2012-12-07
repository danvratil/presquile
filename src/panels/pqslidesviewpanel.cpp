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

PQSlidesViewPanel::PQSlidesViewPanel(MainWindow* parent, Qt::WindowFlags flags)
  : QDockWidget(tr("Slides"), parent, flags)
{
  mSlidesListwidget = new QListView(this);
  mSlidesListwidget->setModel(parent->slidesModel());
  mSlidesListwidget->setItemDelegate(new PQSlidesModelDelegate(mSlidesListwidget));
  mSlidesListwidget->setDragDropMode(QAbstractItemView::InternalMove);
  mSlidesListwidget->setDragEnabled(true);
  mSlidesListwidget->setSelectionMode(QAbstractItemView::SingleSelection);

  connect(mSlidesListwidget, SIGNAL(activated(QModelIndex)),
          this, SLOT(currentItemChanged(QModelIndex)));

  setWidget(mSlidesListwidget);
}

PQSlidesViewPanel::~PQSlidesViewPanel()
{

}

void PQSlidesViewPanel::currentItemChanged(const QModelIndex &index)
{
    PQSlide::Ptr slide = index.data(PQSlidesModel::PQSlideRole).value<PQSlide::Ptr>();

    Q_EMIT slideActivated(slide);
}



#include "pqslidesviewpanel.moc"