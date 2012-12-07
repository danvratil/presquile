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
#include <QGraphicsItem>

PQSlide::PQSlide(const QString& filePath, QDeclarativeEngine *engine, QObject* parent)
    : QObject(parent)
    , mSlideFilePath(filePath)
    , mEngine(engine)
{

    mContext = new QDeclarativeContext(mEngine, this);
    mComponent = new QDeclarativeComponent(mEngine, QUrl::fromLocalFile(filePath), this);

    /* mScene takes ownership of the instance */
    QObject *instance = mComponent->create(mContext);
    QGraphicsItem *graphicsItem = qobject_cast<QGraphicsItem*>(instance);

    mScene = new QGraphicsScene(this);
    mScene->addItem(graphicsItem);
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

QGraphicsScene* PQSlide::scene() const
{
    return mScene;
}

QString PQSlide::slideFilePath() const
{
    return mSlideFilePath;
}

#include "pqslide.moc"
