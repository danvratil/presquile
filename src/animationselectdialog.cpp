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

#include "animationselectdialog.h"

#include <QGridLayout>
#include <QTreeWidget>
#include <QDialogButtonBox>
#include <QStringBuilder>
#include <QDesktopServices>
#include <QDebug>
#include <QDeclarativeComponent>
#include <QDeclarativeEngine>

#include "coreutils.h"

Q_DECLARE_METATYPE(QSharedPointer<QObject>);

AnimationSelectDialog::AnimationSelectDialog(QDeclarativeEngine *engine, QWidget* parent)
    : QDialog(parent)
    , mEngine(engine)
{
    setWindowTitle(tr("Select Animation"));
    setModal(true);
    resize(450, 300);

    mLayout = new QGridLayout(this);
    setLayout(mLayout);

    mAnimationsList = new QTreeWidget(this);
    mAnimationsList->setColumnCount(2);
    mAnimationsList->setHeaderLabels(QStringList() << tr("Name") << tr("Description"));
    mAnimationsList->setColumnWidth(0, 160);
    mAnimationsList->setColumnWidth(1, 250);
    mAnimationsList->setRootIsDecorated(false);
    mAnimationsList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mAnimationsList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mLayout->addWidget(mAnimationsList, 0, 0);
    connect(mAnimationsList, SIGNAL(doubleClicked(QModelIndex)), SLOT(accept()));

    mButtonBox = new QDialogButtonBox(this);
    mButtonBox->addButton(QDialogButtonBox::Ok);
    mButtonBox->addButton(QDialogButtonBox::Cancel);
    connect(mButtonBox, SIGNAL(accepted()), SLOT(accept()));
    connect(mButtonBox, SIGNAL(rejected()), SLOT(reject()));
    mLayout->addWidget(mButtonBox, 1, 0);

    loadAnimations();
}

AnimationSelectDialog::~AnimationSelectDialog()
{

}

QSharedPointer<QObject> AnimationSelectDialog::selectedAnimation() const
{
    if (!mAnimationsList->currentIndex().isValid()) {
	return QSharedPointer<QObject>();
    }

    return mAnimationsList->currentItem()->data(0, ObjectTypeRole).value< QSharedPointer<QObject> >();
}


QSharedPointer<QObject> AnimationSelectDialog::getObject(const QString& qmlFile)
{
    QDeclarativeComponent component(mEngine, CoreUtils::resourcePath() % QLatin1String("/qml/animations/") % qmlFile);
    QSharedPointer<QObject> ptr(component.create(mEngine->rootContext()));

    if (ptr.isNull()) {
      qWarning() << component.errorString();
    }

    return ptr;
}


void AnimationSelectDialog::loadAnimations()
{
    QTreeWidgetItem *item;

    /* TODO: Support dynamic loading from /qml/animations */
    /* TODO: Support loading custom user animations */
    QStringList animations;
    animations << QLatin1String("PropertyAnimation.qml")
	       << QLatin1String("RotationAnimation.qml")
	       << QLatin1String("ColorAnimation.qml")
	       << QLatin1String("NumberAnimation.qml")
	       << QLatin1String("SpringAnimation.qml")
	       << QLatin1String("ParallelAnimation.qml")
	       << QLatin1String("PauseAnimation.qml");

    Q_FOREACH(const QString &animation, animations) {
	QSharedPointer<QObject> obj = getObject(animation);
	item = new QTreeWidgetItem(mAnimationsList);
	item->setText(0, obj->property("_PQDisplayName").toString());
	item->setText(1, obj->property("_PQDescription").toString());
	item->setData(0, ObjectTypeRole, QVariant::fromValue(obj));
	mAnimationsList->addTopLevelItem(item);
    }
}


#include "animationselectdialog.moc"