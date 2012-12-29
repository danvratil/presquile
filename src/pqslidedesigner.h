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

#ifndef PQSLIDEDESIGNER_H
#define PQSLIDEDESIGNER_H

#include <QDeclarativeView>
#include "pqslide.h"

class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;
class QDeclarativeItem;

class PQSlideDesigner : public QDeclarativeView
{
    Q_OBJECT

public:
    explicit PQSlideDesigner(QWidget* parent = 0);
    virtual ~PQSlideDesigner();

public Q_SLOTS:
    void setSlide(const PQSlide::Ptr &slide);

Q_SIGNALS:
    void focusedItemChanged(QObject *item);

private Q_SLOTS:
    void slotItemFocusChanged(bool hasFocus);
    void slotItemDoubleClicked();

protected:
    virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void dragMoveEvent(QDragMoveEvent *event);
    virtual void dropEvent(QDropEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *event);

private:
    QDeclarativeItem* slideRoot() const;
    QDeclarativeItem* slideRect() const;
    QDeclarativeItem* slideChildrenContainer() const;

    PQSlide::Ptr mCurrentSlide;

};

#endif // PQSLIDEDESIGNER_H
