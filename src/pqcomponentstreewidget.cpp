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

#include "pqcomponentstreewidget.h"

#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QApplication>
#include <QStringBuilder>
#include <QDebug>

PQComponentsTreeWidget::PQComponentsTreeWidget(QWidget* parent)
    : QTreeWidget(parent)
{
    setColumnCount(1);
    setHeaderHidden(true);

    QTreeWidgetItem *item, *category;

    category = new QTreeWidgetItem(this);
    category->setText(0, tr("Basic"));
    addTopLevelItem(category);

    item = new QTreeWidgetItem(category);
    item->setText(0, tr("Rectangle"));
    item->setData(0, ComponentNameRole, QLatin1String("PQRectangle"));
    category->addChild(item);

    item = new QTreeWidgetItem(category);
    item->setText(0, tr("Text"));
    item->setData(0, ComponentNameRole, QLatin1String("PQText"));
    category->addChild(item);

    item = new QTreeWidgetItem(category);
    item->setText(0, tr("Button"));
    item->setData(0, ComponentNameRole, QLatin1String("Button"));
    category->addChild(item);

    item = new QTreeWidgetItem(category);
    item->setText(0, tr("Image"));
    item->setData(0, ComponentNameRole, QLatin1String("PQImage"));
    category->addChild(item);

    item = new QTreeWidgetItem(category);
    item->setText(0, tr("Animated Image"));
    item->setData(0, ComponentNameRole, QLatin1String("PQAnimatedImage"));
    category->addChild(item);
}

PQComponentsTreeWidget::~PQComponentsTreeWidget()
{

}

void PQComponentsTreeWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
         mLastClickPos = event->pos();
    }

    /* First select current item etc */
    QTreeWidget::mousePressEvent(event);
}

void PQComponentsTreeWidget::mouseMoveEvent(QMouseEvent* event)
{
    QTreeWidgetItem *item = currentItem();

    if (item->parent() == 0) {
	return;
    }

    if (!(event->buttons() & Qt::LeftButton)) {
	return;
    }

    if ((event->pos() - mLastClickPos).manhattanLength() < QApplication::startDragDistance()) {
	return;
    }

    QMimeData *mimeData = new QMimeData;
    mimeData->setText(QLatin1String("Component/") % item->data(0, ComponentNameRole).toString());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction);
}


#include "pqcomponentstreewidget.moc"
