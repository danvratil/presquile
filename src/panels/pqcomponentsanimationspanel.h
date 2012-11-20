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

#ifndef PQCOMPONENTSANIMATIONSPANEL_H
#define PQCOMPONENTSANIMATIONSPANEL_H

#include <QDockWidget>
#include <QPointer>

class TransformationsEditor;
class PQComponentsAnimationsPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit PQComponentsAnimationsPanel(QWidget* parent = 0);
    virtual ~PQComponentsAnimationsPanel();

public Q_SLOTS:
    void setItem(QObject *item);

private:
    QPointer<QObject> mObject;

    TransformationsEditor *mTransformationsEditor;
};

#endif // PQCOMPONENTSANIMATIONSPANEL_H
