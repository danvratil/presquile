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

#include "animationsequenceeditor.h"
#include "propertieseditor.h"
#include "../animationselectdialog.h"

#include <QTreeWidget>
#include <QSplitter>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPointer>
#include <QDeclarativeEngine>
#include <QDialogButtonBox>

Q_DECLARE_METATYPE(QPointer<QObject>);

AnimationSequenceEditor::AnimationSequenceEditor(QWidget* parent)
    : QDialog(parent)
    , mEngine(new QDeclarativeEngine(this))
{
    setWindowTitle(tr("Animation Editor"));
    setModal(true);

    QVBoxLayout *vBoxLayout = new QVBoxLayout(this);
    setLayout(vBoxLayout);

    mSplitter = new QSplitter(Qt::Horizontal, this);
    vBoxLayout->addWidget(mSplitter);

    mGridLayout = new QGridLayout(mSplitter);

    QLabel *label = new QLabel(tr("Template:"), this);
    mGridLayout->addWidget(label, 0, 0);

    mAnimationTemplatesCombo = new QComboBox(this);
    mGridLayout->addWidget(mAnimationTemplatesCombo, 0, 1, 1, 6);

    mAnimationsTree = new QTreeWidget(this);
    mAnimationsTree->setHeaderHidden(true);
    mAnimationsTree->setAnimated(true);
    mGridLayout->addWidget(mAnimationsTree, 1, 0, 1, 5);
    connect(mAnimationsTree, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), SLOT(slotCurrentItemChanged()));

    QTreeWidgetItem *rootItem = new QTreeWidgetItem(mAnimationsTree);
    rootItem->setText(0, tr("Root Animation"));
    mAnimationsTree->addTopLevelItem(rootItem);

    mAddAnimationButton = new QPushButton(QIcon::fromTheme(QLatin1String("list-add")), QString(), this);
    mAddAnimationButton->setToolTip(tr("Add Animation"));
    connect(mAddAnimationButton, SIGNAL(clicked(bool)), SLOT(slotAddAnimation()));
    mGridLayout->addWidget(mAddAnimationButton, 2, 0);

    mRemoveAnimationButton = new QPushButton(QIcon::fromTheme(QLatin1String("list-remove")), QString(), this);
    mRemoveAnimationButton->setToolTip(tr("Remove Animation"));
    connect(mRemoveAnimationButton, SIGNAL(clicked(bool)), SLOT(slotRemoveAnimation()));
    mGridLayout->addWidget(mRemoveAnimationButton, 2, 1);

    mMoveAnimationUpButton = new QPushButton(QIcon::fromTheme(QLatin1String("arrow-up")), QString(), this);
    mMoveAnimationUpButton->setToolTip(tr("Move Up"));
    connect(mMoveAnimationUpButton, SIGNAL(clicked(bool)), SLOT(slotMoveAnimationUp()));
    mGridLayout->addWidget(mMoveAnimationUpButton, 2, 2);

    mMoveAnimsationDownButton = new QPushButton(QIcon::fromTheme(QLatin1String("arrow-down")), QString(), this);
    mMoveAnimsationDownButton->setToolTip(tr("Move Down"));
    connect(mMoveAnimsationDownButton, SIGNAL(clicked(bool)), SLOT(slotMoveAnimationDown()));
    mGridLayout->addWidget(mMoveAnimsationDownButton, 2, 3);
    mGridLayout->setColumnStretch(4, 2);

    QWidget *widget = new QWidget(this);
    widget->setLayout(mGridLayout);
    mSplitter->addWidget(widget);

    mPropertiesEditor = new PropertiesEditor(this);
    mSplitter->addWidget(mPropertiesEditor);

    mButtonBox = new QDialogButtonBox(this);
    mButtonBox->addButton(QDialogButtonBox::Ok);
    mButtonBox->addButton(QDialogButtonBox::Cancel);
    connect(mButtonBox, SIGNAL(accepted()), SLOT(accept()));
    connect(mButtonBox, SIGNAL(rejected()), SLOT(reject()));
    vBoxLayout->addWidget(mButtonBox);

    mAnimationsTree->setCurrentItem(rootItem);
}

AnimationSequenceEditor::~AnimationSequenceEditor()
{

}

void AnimationSequenceEditor::slotCurrentItemChanged()
{
    QTreeWidgetItem *currentItem = mAnimationsTree->currentItem();
    if (!currentItem) {
	mAddAnimationButton->setEnabled(false);
	mRemoveAnimationButton->setEnabled(false);
	mMoveAnimationUpButton->setEnabled(false);
	mMoveAnimsationDownButton->setEnabled(false);
	mPropertiesEditor->setObject(0);
	return;
    }

    QPointer<QObject> obj = currentItem->data(0, ObjectRole).value< QPointer<QObject> >();
    /* Top-level item */
    if (obj.isNull()) {
      mAddAnimationButton->setEnabled(true);
      mRemoveAnimationButton->setEnabled(false);
      mMoveAnimationUpButton->setEnabled(false);
      mMoveAnimsationDownButton->setEnabled(false);
      mPropertiesEditor->setObject(0);
      return;
    }

    mAddAnimationButton->setEnabled(obj->property("_PQCanHaveChildren").toBool());
    mRemoveAnimationButton->setEnabled(true);

    int row = currentItem->parent()->indexOfChild(currentItem);
    mMoveAnimationUpButton->setEnabled((row != 0));

    int count = currentItem->parent()->childCount();
    mMoveAnimsationDownButton->setEnabled((row < count - 1));

    mPropertiesEditor->setObject(obj);
}

void AnimationSequenceEditor::slotAddAnimation()
{
    QScopedPointer<AnimationSelectDialog> dlg(new AnimationSelectDialog(mEngine, this));
    if (dlg->exec() != QDialog::Accepted) {
	return;
    }

    QPointer<QObject> animation = dlg->selectedAnimation();

    QTreeWidgetItem* currentItem = mAnimationsTree->currentItem();
    if (!currentItem) {
	return;
    }

    QTreeWidgetItem *item = new QTreeWidgetItem(currentItem);
    item->setText(0, animation->property("_PQDisplayName").toString());
    item->setData(0, ObjectRole, QVariant::fromValue(animation));

    mAnimationsTree->expandItem(currentItem);
}

void AnimationSequenceEditor::slotRemoveAnimation()
{
    QTreeWidgetItem *currentItem = mAnimationsTree->currentItem();
    if (!currentItem) {
	return;
    }


    int row = currentItem->parent()->indexOfChild(currentItem);
    delete currentItem->parent()->takeChild(row);
}

void AnimationSequenceEditor::slotMoveAnimationUp()
{
    QTreeWidgetItem *currentItem = mAnimationsTree->currentItem();
    if (!currentItem) {
	return;
    }

    QTreeWidgetItem *parent = currentItem->parent();
    int row = parent->indexOfChild(currentItem);

    parent->takeChild(row);
    parent->insertChild(row - 1, currentItem);

    mAnimationsTree->setCurrentItem(currentItem);
}

void AnimationSequenceEditor::slotMoveAnimationDown()
{
    QTreeWidgetItem *currentItem = mAnimationsTree->currentItem();
    if (!currentItem) {
	return;
    }

    QTreeWidgetItem *parent = currentItem->parent();
    int row = parent->indexOfChild(currentItem);

    if (row >= parent->childCount() - 1) {
	return;
    }

    parent->takeChild(row);
    parent->insertChild(row + 1, currentItem);

    mAnimationsTree->setCurrentItem(currentItem);
}



#include "animationsequenceeditor.moc"