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

#include "pqqmlloader.h"
#include "pqstandarddirs.h"

#include <QMutex>
#include <QStringBuilder>
#include <QDeclarativeComponent>
#include <QDeclarativeEngine>
#include <QDeclarativeItem>
#include <QDebug>
#include <QFile>


//#include "pqtext.h"

PQQmlLoader *PQQmlLoader::mInstance = 0;

PQQmlLoader* PQQmlLoader::instance()
{
    static QMutex instanceLock;

    instanceLock.lock();
    if (mInstance == 0) {
        mInstance = new PQQmlLoader();
    }
    instanceLock.unlock();

    return mInstance;
}


PQQmlLoader::PQQmlLoader()
    : QObject()
{
    /* TODO: Components should be plugins that can be loaded dynamically */


}

PQQmlLoader::~PQQmlLoader()
{

}

QDeclarativeItem* PQQmlLoader::componentInstance(QDeclarativeEngine *engine, const QString& componentName)
{
    if (!QFile::exists(PQStandardDirs::qmlImportFile(componentName % QLatin1String(".qml"), PQStandardDirs::Component))) {
        qWarning() << componentName << "source file does not exist";
        return 0;
    }

    QByteArray ba;
    ba.append("import QtQuick 1.0\n\n"
              "import Presquile 1.0\n\n").
       append(componentName.toLatin1()).
       append("{ }");

    QDeclarativeComponent component(engine, this);
    component.setData(ba, QUrl::fromLocalFile(PQStandardDirs::qmlImportDir(PQStandardDirs::Component)));

    QObject *instance = component.create(engine->rootContext());
    if (!instance) {
        qWarning() << "Failed to construct" << componentName << ":" << component.errorString();
        return 0;
    }

    return qobject_cast<QDeclarativeItem*>(instance);
}
