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
#include "pqbaseitem.h"
#include <QMetaObject>
#include <QStringList>
#include <QTextStream>
#include <QDeclarativeProperty>
#include <QDeclarativeListReference>

PQBaseItem::PQBaseItem(QDeclarativeItem *parent): QDeclarativeItem(parent)
{
    // Fill extra properties
    extraProperties.append("transform"); // it has its own extra editor
}

QString PQBaseItem::serializeProperty(const QDeclarativeProperty &property, unsigned indentSize, const QString &indentStep)
{
    QString value, rawValue;

    if (property.propertyTypeCategory() == QDeclarativeProperty::Normal) // Normal value property
    {
        int propertyType = property.propertyType();
        if (propertyType >= QVariant::Bool && propertyType <= QVariant::Double) // Numerical, unquoted values
          value = property.read().toString();
        else
        {
          if (!(rawValue = property.read().toString()).isEmpty())
            value = '"' + property.read().toString()
                    .replace('\\', "\\\\") // escape backslashes in rich text
                    .replace('"', "\\\"") // escape quotes
                    + '"';
        }
    }
    else if (property.propertyTypeCategory() == QDeclarativeProperty::Object) // Complex Object type
    {
        QVariant variantValue = property.read();
        if (variantValue.isValid() && !variantValue.isNull()) {
            value = serializeObject(variantValue.value<QObject *>(), indentSize, indentStep);
        }
    }
    else if (property.propertyTypeCategory() == QDeclarativeProperty::List) // List of objects
    {
        QDeclarativeListReference list = qvariant_cast<QDeclarativeListReference>(property.read());

        value = "[\n"; // open list
        for (int itemIndex(0); itemIndex < list.count(); ++itemIndex) {
            QObject *item = list.at(itemIndex);
            value += serializeObject(item, indentSize+1, indentStep);
            if (itemIndex + 1 != list.count()) value += ','; // separator
            value += '\n';
        }
        value += indentStep.repeated(indentSize) + "]"; // close list
    }

    if (!value.isEmpty()) return indentStep.repeated(indentSize) + property.name() + ": " + value + '\n';
    else return QString();
}

QString PQBaseItem::serializeObject(const QObject *object, unsigned indentSize, const QString &indentStep)
{
    QString value;
    const QMetaObject *objectInfo;

    if (object == 0) return value; // empty string
    objectInfo = object->metaObject();

    // Handle object name
    QString objectName(objectInfo->className());
    // Some QML objects instantiates directly C++ classes, the name must be stripedd of Q* prefix
    QStringList unwantedPrefixes;
    unwantedPrefixes.append("QGraphics");
    unwantedPrefixes.append("QDeclarative");
    Q_FOREACH (const QString &prefix, unwantedPrefixes) {
        if (objectName.startsWith(prefix)) objectName.remove(0, prefix.length());
    }

    value += indentStep.repeated(indentSize) + objectName + " {\n"; // open object
    for (int i(objectInfo->propertyOffset()); i < objectInfo->propertyCount(); ++i) {
        value += serializeProperty(QDeclarativeProperty(const_cast<QObject *>(object), objectInfo->property(i).name()), indentSize+1, indentStep);
    }
    value += indentStep.repeated(indentSize) + "}"; // close object

    return value;
}

/**
 * Serializes the object into valid QML string.
 * @param baseIndentSize Number of indenting steps
 * @param indentStep String representing the indent, default to two spaces
 * @return Serialized QML object
 */
QString PQBaseItem::serialize(const unsigned &baseIndentSize, const QString &indentStep) const
{
    unsigned indentSize = baseIndentSize;

    QString output; // Serialized object
    QTextStream outStream(&output, QIODevice::WriteOnly);

    QStringList properties(property("_PQProperties").toStringList());

    // Open self declaration
    outStream << indentStep.repeated(indentSize) << qmlName() << " {" << endl;
    ++indentSize;

    Q_FOREACH(const QString &currentPropertyName, properties+extraProperties)
    {
        QDeclarativeProperty currentProperty(const_cast<PQBaseItem *>(this), currentPropertyName);
        outStream << serializeProperty(currentProperty, indentSize, indentStep);
    }

    // Close self declaration
    --indentSize;
    outStream << indentStep.repeated(indentSize) << '}' << endl;

    return output;
}

#include "pqbaseitem.moc"
