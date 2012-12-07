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

#include "pqqmlmanager.h"

#include <QMutex>
#include <QStringBuilder>
#include <QDeclarativeComponent>
#include <QDeclarativeEngine>
#include <QDeclarativeItem>
#include <QDebug>
#include <QFile>

#include "../coreutils.h"
#include "pqitemframe.h"

//#include "pqtext.h"

PQQMLManager *PQQMLManager::mInstance = 0;

PQQMLManager* PQQMLManager::instance()
{
    static QMutex instanceLock;

    instanceLock.lock();
    if (mInstance == 0) {
	mInstance = new PQQMLManager();
    }
    instanceLock.unlock();

    return mInstance;
}


PQQMLManager::PQQMLManager()
    : QObject()
{
    /* TODO: Components should be plugins that can be loaded dynamically */

    qmlRegisterType<PQItemFrame>("Presquile", 1, 0, "PQItemFrame");

}

PQQMLManager::~PQQMLManager()
{

}

QDeclarativeItem* PQQMLManager::componentInstance(QDeclarativeEngine *engine, const QString& componentName)
{
    if (!QFile::exists(CoreUtils::resourcePath() % QLatin1String("/qml/components/") % componentName % QLatin1String(".qml"))) {
	qWarning() << componentName << "source file does not exist";
	return 0;
    }

    QByteArray ba;
    ba.append("import QtQuick 1.0\n\n").
	      //"import Presquile 0.1\n\n").
       append(componentName.toLatin1()).
       append("{ }");

    QDeclarativeComponent component(engine, this);
    component.setData(ba, QUrl::fromLocalFile(CoreUtils::resourcePath() % QLatin1String("/qml/components/")));

    QObject *instance = component.create(engine->rootContext());
    if (!instance) {
	qWarning() << "Failed to construct" << componentName << ":" << component.errorString();
	return 0;
    }

    return qobject_cast<QDeclarativeItem*>(instance);
}


#include "pqqmlmanager.moc"
