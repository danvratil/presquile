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
#ifndef PRESQUILE_CORE_PQBASEITEM_H
#define PRESQUILE_CORE_PQBASEITEM_H

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

public:
    explicit PQBaseItem(QDeclarativeItem *parent = 0);

    /** @brief Name of the object as understood by QML */
    QString qmlName() const;

    /** @brief String containing the serialized object
     *
     * Serializes the object into valid QML string.
     * @param baseIndentSize Number of indenting steps
     * @return Serialized QML object
     */
    QString serialize(const unsigned &baseIndentSize = 0) const;

private:
    /** @brief Serializes one property of QML object */
    QString serializeProperty(const QDeclarativeProperty &property, unsigned indentSize) const;
    /** @brief Serializes one complete QML object */
    QString serializeObject(const QObject *object, unsigned indentSize) const;


    /** @brief Extra properties that are not edited in properties editor, but still should be serialized */
    QStringList extraProperties;

    static QString sIndentStep;
};

// Inline methods

/**
 * Modifies the QtMetaObject::className() and return an actual QML name.
 * It is a bit of hack, but no more elagant solution exists.
 * @return Actual QML name of the object
 */
inline QString PQBaseItem::qmlName() const {
  return QString::fromLatin1(metaObject()->className()).remove(QRegExp(QLatin1String("_QMLTYPE_[0-9]+$")));
}

#endif // PRESQUILE_CORE_PQBASEITEM_H
