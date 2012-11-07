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

#ifndef ANIMATIONSEQUENCEEDITOR_H
#define ANIMATIONSEQUENCEEDITOR_H

#include <QDialog>

class QDeclarativeEngine;
class QTreeWidget;
class QGridLayout;
class QPushButton;
class QComboBox;
class QSplitter;
class QDialogButtonBox;

class PropertiesEditor;

class AnimationSequenceEditor : public QDialog
{
    Q_OBJECT

public:
    enum Roles {
	ObjectRole = Qt::UserRole + 1,
    };
    explicit AnimationSequenceEditor(QWidget* parent = 0);
    virtual ~AnimationSequenceEditor();


private Q_SLOTS:
    void slotAddAnimation();
    void slotRemoveAnimation();
    void slotMoveAnimationUp();
    void slotMoveAnimationDown();

    void slotCurrentItemChanged();

private:
    QDeclarativeEngine *mEngine;

    QSplitter *mSplitter;
    QGridLayout *mGridLayout;
    QTreeWidget *mAnimationsTree;

    QPushButton *mAddAnimationButton;
    QPushButton *mRemoveAnimationButton;
    QPushButton *mMoveAnimationUpButton;
    QPushButton *mMoveAnimsationDownButton;
    QComboBox *mAnimationTemplatesCombo;
    QDialogButtonBox *mButtonBox;

    PropertiesEditor *mPropertiesEditor;
};

#endif // ANIMATIONSEQUENCEEDITOR_H
