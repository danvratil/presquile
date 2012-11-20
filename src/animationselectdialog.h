/*
 * <one line to give the program's name and a brief idea of what it does.>
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

#ifndef ANIMATIONSELECTDIALOG_H
#define ANIMATIONSELECTDIALOG_H

#include <QDialog>

class QGridLayout;
class QTreeWidget;
class QDialogButtonBox;
class QDeclarativeEngine;
class QDeclarativeContext;

class AnimationSelectDialog : public QDialog
{
    Q_OBJECT

public:
    enum Roles {
      ObjectTypeRole = Qt::UserRole + 1,
    };

    explicit AnimationSelectDialog(QDeclarativeEngine *engine, QWidget* parent = 0);
    virtual ~AnimationSelectDialog();

    QObject* selectedAnimation() const;

private:
    void loadAnimations();
    QObject* getObject(const QString &qmlFile);

    QGridLayout *mLayout;
    QTreeWidget *mAnimationsList;
    QDialogButtonBox *mButtonBox;

    QDeclarativeEngine *mEngine;
};

#endif // ANIMATIONSELECTDIALOG_H
