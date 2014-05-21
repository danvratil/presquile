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

#include "pqstandarddirs.h"

#include <QDir>
#include <QCoreApplication>
#include <QLibraryInfo>
#include <QDebug>
#include <QStringBuilder>


class PQStandardDirsPrivate
{
    public:
        static PQStandardDirsPrivate* instance()
        {
            if (!sInstance) {
                sInstance = new PQStandardDirsPrivate;
            }
            return sInstance;
        }


    QString qmlImportPath;

    private:
        static PQStandardDirsPrivate *sInstance;
};

PQStandardDirsPrivate* PQStandardDirsPrivate::sInstance = 0;



QString PQStandardDirs::qmlImportDir(PQStandardDirs::QMLImportType importType)
{
    PQStandardDirsPrivate *d = PQStandardDirsPrivate::instance();
    QString basePath;

    if (!d->qmlImportPath.isEmpty()) {
        basePath = d->qmlImportPath;
    } else {
        // FIXME: Only really works on UNIX
        const QList<QByteArray> importPaths = qgetenv("QML_IMPORT_PATH").split(':');
        Q_FOREACH (const QByteArray &importPath, importPaths) {
            QDir dir(importPath + "/Presquile");
            if (dir.exists()) {
                d->qmlImportPath = QString::fromLatin1(importPath + "/Presquile");
                qDebug() << "PQStandardDirs::resourcePath()" << d->qmlImportPath;
                basePath = d->qmlImportPath;
                break;
            }
        }

        if (basePath.isEmpty()) {
            // Fallback
            d->qmlImportPath = QDir::cleanPath(QLibraryInfo::location(QLibraryInfo::ImportsPath) + QLatin1String("/Presquile/"));
            qDebug() << "PQStandardDirs::resourcePath()" << d->qmlImportPath;
            basePath = d->qmlImportPath;
        }
    }

    switch (importType) {
    case Animation:
        return basePath % QLatin1String("/animations");
    case Component:
        return basePath % QLatin1String("/components");
    case Skeleton:
        return basePath % QLatin1String("/skeleton");
    }

    Q_ASSERT(false);
    return QString();
}


QString PQStandardDirs::qmlImportFile(const QString &qmlFileName, PQStandardDirs::QMLImportType importType)
{
    return qmlImportDir(importType) % QLatin1Char('/') % qmlFileName;
}
