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

QString PQBaseItem::sIndentStep = QLatin1String("  ");

PQBaseItem::PQBaseItem(QDeclarativeItem *parent): QDeclarativeItem(parent)
{
    // Fill extra properties
    extraProperties.append(QLatin1String("transform")); // it has its own extra editor
}

QString PQBaseItem::serializeProperty(const QDeclarativeProperty &property, unsigned indentSize) const
{
    QString value, rawValue;

    if (property.propertyTypeCategory() == QDeclarativeProperty::Normal) { // Normal value property
        const int propertyType = property.propertyType();
        const QString propertyValue = property.read().toString();
        if (propertyType >= QVariant::Bool && propertyType <= QVariant::Double) { // Numerical, unquoted values
            value = propertyValue;
        } else {
            if (!propertyValue.isEmpty()) {
                value = propertyValue;
                value.replace(QLatin1Char('\\'), QLatin1String("\\\\")) // escape backslashes in rich text
                     .replace(QLatin1Char('"'), QLatin1String("\\\"")); // escape quotes
                value = QLatin1Char('"') % value % QLatin1Char('"');
            }
        }
    } else if (property.propertyTypeCategory() == QDeclarativeProperty::Object) { // Complex Object type
        const QVariant variantValue = property.read();
        if (variantValue.isValid() && !variantValue.isNull()) {
            value = serializeObject(variantValue.value<QObject *>(), indentSize);
        }
    } else if (property.propertyTypeCategory() == QDeclarativeProperty::List) { // List of objects
        const QDeclarativeListReference list = qvariant_cast<QDeclarativeListReference>(property.read());

        value = QLatin1String("[\n"); // open list
        for (int itemIndex = 0, c = list.count(); itemIndex < c; ++itemIndex) {
            QObject *item = list.at(itemIndex);
            value += serializeObject(item, indentSize+1);
            if (itemIndex + 1 != list.count()) {
                value += QLatin1Char(','); // separator
            }
            value += QLatin1Char('\n');
        }
        value += sIndentStep.repeated(indentSize) + QLatin1String("]"); // close list
    }

    if (!value.isEmpty()) {
        return sIndentStep.repeated(indentSize) + property.name() + QLatin1String(": ") + value + QLatin1Char('\n');
    }

    return QString();
}

QString PQBaseItem::serializeObject(const QObject *object, unsigned indentSize) const
{
    QString value;
    const QMetaObject *objectInfo;

    if (object == 0) {
        return value; // empty string
    }
    objectInfo = object->metaObject();

    // Handle object name
    QString objectName = QString::fromLatin1(objectInfo->className());
    // Some QML objects instantiates directly C++ classes, the name must be stripedd of Q* prefix
    static QStringList unwantedPrefixes =
        QStringList() << QLatin1String("QGraphics")
                      << QLatin1String("QDeclarative");
    Q_FOREACH (const QString &prefix, unwantedPrefixes) {
        if (objectName.startsWith(prefix)) {
            objectName.remove(0, prefix.length());
        }
    }

    value += sIndentStep.repeated(indentSize) + objectName + QLatin1String(" {\n"); // open object
    for (int i = objectInfo->propertyOffset(); i < objectInfo->propertyCount(); ++i) {
        value += serializeProperty(QDeclarativeProperty(const_cast<QObject *>(object),
                                                        QString::fromLatin1(objectInfo->property(i).name())),
                                   indentSize + 1);
    }
    value += sIndentStep.repeated(indentSize) + QLatin1String("}"); // close object

    return value;
}

QString PQBaseItem::serialize(const unsigned &baseIndentSize) const
{
    unsigned indentSize = baseIndentSize;

    QString output; // Serialized object
    QTextStream outStream(&output, QIODevice::WriteOnly);

    QStringList properties(property("_PQProperties").toStringList());

    // Open self declaration
    outStream << sIndentStep.repeated(indentSize) << qmlName() << QLatin1String(" {") << endl;
    ++indentSize;

    Q_FOREACH(const QString &currentPropertyName, properties+extraProperties) {
        QDeclarativeProperty currentProperty(const_cast<PQBaseItem *>(this), currentPropertyName);
        outStream << serializeProperty(currentProperty, indentSize);
    }

    // Close self declaration
    --indentSize;
    outStream << sIndentStep.repeated(indentSize) << QLatin1Char('}') << endl;

    return output;
}

#include "pqbaseitem.moc"
