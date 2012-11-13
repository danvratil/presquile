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

#ifndef PQCOMPONENTSTREEWIDGET_H
#define PQCOMPONENTSTREEWIDGET_H

#include <QTreeWidget>
#include <QPoint>


class PQComponentsTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    enum Roles {
	ComponentNameRole = Qt::UserRole + 1,
    };

    explicit PQComponentsTreeWidget(QWidget* parent = 0);
    virtual ~PQComponentsTreeWidget();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);


private:
    QPoint mLastClickPos;
    bool mDragActive;
};

#endif // PQCOMPONENTSTREEWIDGET_H
