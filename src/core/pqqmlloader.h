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

#ifndef PRESQUILE_CORE_PQQMLLOADER_H
#define PRESQUILE_CORE_PQQMLLOADER_H

#include "presquile-core-export.h"

#include <QObject>

class QDeclarativeItem;
class QDeclarativeEngine;

class PRESQUILECORE_EXPORT PQQmlLoader : public QObject
{
    Q_OBJECT
public:
    static PQQmlLoader* instance();

    QDeclarativeItem* componentInstance(QDeclarativeEngine *engine, const QString &componentName);


private:
    explicit PQQmlLoader();
    virtual ~PQQmlLoader();

    static PQQmlLoader *mInstance;
};

#endif // PRESQUILE_CORE_PQQMLLOADER_H
