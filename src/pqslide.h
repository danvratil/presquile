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

#ifndef PQSLIDE_H
#define PQSLIDE_H

#include <QObject>
#include <QPointer>
#include <QSharedPointer>
#include <QMetaType>

class QDeclarativeEngine;
class QDeclarativeContext;
class QDeclarativeComponent;

class PQSlide : public QObject
{
    Q_OBJECT

  public:
    typedef QSharedPointer<PQSlide> Ptr;

    explicit PQSlide(const QString &filePath, QDeclarativeEngine *engine, QObject* parent = 0);
    explicit PQSlide(QDeclarativeComponent *slideData, QDeclarativeEngine *engine, QObject* parent = 0);
    virtual ~PQSlide();

    QString slideFilePath() const;
    QDeclarativeEngine* engine() const;
    QDeclarativeContext* context() const;
    QDeclarativeComponent* component() const;
    QObject* rootObject() const;

  private:
    QString mSlideFilePath;
    QPointer<QDeclarativeEngine> mEngine;
    QPointer<QDeclarativeContext> mContext;
    QPointer<QDeclarativeComponent> mComponent;
    QPointer<QObject> mRootObject;

};

Q_DECLARE_METATYPE(PQSlide::Ptr)

#endif // PQSLIDE_H
