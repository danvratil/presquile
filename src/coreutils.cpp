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

#include "coreutils.h"

#include <QDir>
#include <QCoreApplication>
#include <QLibraryInfo>
#include <QDebug>

QString CoreUtils::resourcePath()
{
#ifdef DEBUG_MODE
    /* For development purposes, first check for "/data" subfolder or ../../data (in
     * case of out-of-source build) */
    QDir d(QCoreApplication::applicationDirPath() + QLatin1String("/data"));
    if (d.exists()) {
        return d.absolutePath();
    }

    d.setPath(QCoreApplication::applicationDirPath() + QLatin1String("/../../data/"));
    if (d.exists()) {
        return d.absolutePath();
    }
#endif

#ifdef MODULEDIR
    qDebug() << QDir::cleanPath(QLatin1String(MODULEDIR));
    return QDir::cleanPath(QLatin1String(MODULEDIR));
#else
    qDebug() << QDir::cleanPath(QLibraryInfo::location(QLibraryInfo::ImportsPath) + QLatin1String("/Presquile/"));
    return QDir::cleanPath(QLibraryInfo::location(QLibraryInfo::ImportsPath) + QLatin1String("/Presquile/"));
#endif
}

