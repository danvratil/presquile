/** PQBaseItem -- Base class of serializable components
 *  Copyright (C) 2014 Jan Stanek <khardix@gmail.com>
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PQBASEITEM_H
#define PQBASEITEM_H

#include "presquile-core-export.h"

#include <QDeclarativeItem>
#include <QString>

class QDeclarativeProperty;

/**
 * Ancestor for all presentation QML objects.
 *
 * This class implements the object identification and serialization.
 * @author Jan Stanek
 */
class PRESQUILECORE_EXPORT PQBaseItem : public QDeclarativeItem
{
    Q_OBJECT

    /** @brief Serializes one property of QML object */
    static QString serializeProperty(const QDeclarativeProperty &property, unsigned indentSize, const QString &indentStep = "  ");
    /** @brief Serializes one complete QML object */
    static QString serializeObject(const QObject *object, unsigned indentSize, const QString &indentStep = "  ");
public:
    explicit PQBaseItem(QDeclarativeItem *parent = 0);

    /** @brief Name of the object as understood by QML */
    QString qmlName() const;

    /** @brief String containing the serialized object */
    QString serialize(const unsigned &baseIndentSize = 0, const QString &indentStep = "  ") const;

private:
    /** @brief Extra properties that are not edited in properties editor, but still should be serialized */
    QStringList extraProperties;
};

// Inline methods

/**
 * Modifies the QtMetaObject::className() and return an actual QML name.
 * It is a bit of hack, but no more elagant solution exists.
 * @return Actual QML name of the object
 */
inline QString PQBaseItem::qmlName() const {
  return QString(metaObject()->className()).remove(QRegExp("_QMLTYPE_[0-9]+$"));
}

#endif // PQBASEITEM_H
