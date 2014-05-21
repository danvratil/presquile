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

static QString s_importPath;


QString CoreUtils::resourcePath()
{
    if (!s_importPath.isEmpty()) {
        return s_importPath;
    }

    const QList<QByteArray> importPaths = qgetenv("QML_IMPORT_PATH").split(':');
    Q_FOREACH (const QByteArray &importPath, importPaths) {
        QDir dir(importPath + "/Presquile");
        if (dir.exists()) {
            s_importPath = importPath + "/Presquile";
            qDebug() << "CoreUtils::resourcePath()" << s_importPath;
            return s_importPath;
        }
    }

    // Fallback
    s_importPath = QDir::cleanPath(QLibraryInfo::location(QLibraryInfo::ImportsPath) + QLatin1String("/Presquile/"));
    qDebug() << "CoreUtils::resourcePath()" << s_importPath;
    return s_importPath;
}

