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


#include "pqslide.h"

#include <QGraphicsScene>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeItem>
#include <QGraphicsItem>

PQSlide::PQSlide(const QString& filePath, QDeclarativeEngine *engine, QObject* parent)
    : QObject(parent)
    , mSlideFilePath(filePath)
    , mEngine(engine)
{
    mContext = new QDeclarativeContext(mEngine->rootContext(), this);
    mComponent = new QDeclarativeComponent(mEngine, QUrl::fromLocalFile(filePath), this);

    /* mScene takes ownership of the instance */
    mRootObject = mComponent->create(mContext);
    if (mComponent->isError()) {
        qFatal("%s", qPrintable(mComponent->errorString()));
    }
    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(mRootObject.data());

    /* FIXME: This is a hack to force initial size of the slide. Maybe in this
     * case it would be better to hardcode 800x600 here rather then building
     * the scene. */
    QGraphicsScene scene;
    scene.addItem(item);
    item->setWidth(scene.width());
    item->setHeight(scene.height());
    scene.removeItem(item); /* otherwise scene would destroy the item */
}

PQSlide::PQSlide(QDeclarativeComponent *slideData, QDeclarativeEngine *engine, QObject *parent)
    : QObject(parent)
    , mSlideFilePath()
    , mEngine(engine)
{
    mContext = new QDeclarativeContext(mEngine->rootContext(), this);
    mComponent = slideData;
    mComponent->setParent(this);

    // mScene takes ownership of the instance
    mRootObject = mComponent->create(mContext);
    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(mRootObject.data());

    // FIXME: This is a hack to force initial size of the slide. Maybe in this
    // case it would be better to hardcode 800x600 here rather then building
    // the scene.
    QGraphicsScene scene;
    scene.addItem(item);
    item->setWidth(scene.width());
    item->setHeight(scene.height());
    scene.removeItem(item); // otherwise scene would destroy the item
}

PQSlide::~PQSlide()
{

}

QDeclarativeEngine* PQSlide::engine() const
{
    return mEngine;
}

QDeclarativeContext* PQSlide::context() const
{
    return mContext;
}

QDeclarativeComponent* PQSlide::component() const
{
    return mComponent;
}

QString PQSlide::slideFilePath() const
{
    return mSlideFilePath;
}

QObject* PQSlide::rootObject() const
{
    return mRootObject;
}

#include "pqslide.moc"
