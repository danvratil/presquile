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

#include "pqcomponentsanimationspanel.h"
#include "../editors/transformationseditor.h"
#include <QHBoxLayout>

PQComponentsAnimationsPanel::PQComponentsAnimationsPanel(QWidget* parent)
  : QDockWidget(tr("Animations And Transformations"), parent)
  , mObject(0)
{
    QWidget *mainWidget = new QWidget(this);
    setWidget(mainWidget);

    QHBoxLayout *layout = new QHBoxLayout(mainWidget);

    mTransformationsEditor = new TransformationsEditor(this);
    mTransformationsEditor->setEnabled(false);
    layout->addWidget(mTransformationsEditor);
}

PQComponentsAnimationsPanel::~PQComponentsAnimationsPanel()
{

}

void PQComponentsAnimationsPanel::setItem(QObject* item)
{
    mObject = item;

    mTransformationsEditor->setObject(mObject);
    mTransformationsEditor->setEnabled(item != 0);
}


#include "pqcomponentsanimationspanel.moc"