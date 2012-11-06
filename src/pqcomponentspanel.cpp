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

#include "pqcomponentspanel.h"

#include <QTreeWidget>

PQComponentsPanel::PQComponentsPanel(QWidget* parent, Qt::WindowFlags flags)
  : QDockWidget(tr("Components"), parent, flags)
{
    mTreeWidget = new QTreeWidget(this);
    setWidget(mTreeWidget);

    mTreeWidget->setColumnCount(1);
    mTreeWidget->setHeaderHidden(true);

    loadSystemComponents();
}

PQComponentsPanel::~PQComponentsPanel()
{

}

void PQComponentsPanel::loadSystemComponents()
{
    QTreeWidgetItem *item, *category;

    category = new QTreeWidgetItem(mTreeWidget);
    category->setText(0, tr("Basic"));
    mTreeWidget->addTopLevelItem(category);

    item = new QTreeWidgetItem(category);
    item->setText(0, tr("Label"));
    category->addChild(item);

    item = new QTreeWidgetItem(category);
    item->setText(0, tr("Button"));
    category->addChild(item);

    item = new QTreeWidgetItem(category);
    item->setText(0, tr("Image"));
    category->addChild(item);
}


#include "pqcomponentspanel.moc"
