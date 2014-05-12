#include "pqbaseitem.h"
#include <QMetaObject>
#include <QStringList>
#include <QTextStream>
#include <QDeclarativeProperty>
#include <QDeclarativeListReference>

QString PQBaseItem::serializeProperty(const QDeclarativeProperty &property, unsigned indentSize, const QString &indentStep)
{
    QString value;

    if (property.propertyTypeCategory() == QDeclarativeProperty::Normal) // Normal value property
    {
        int propertyType = property.propertyType();
        if (propertyType >= QVariant::Bool && propertyType <= QVariant::Double) // Numerical, unquoted values
          value = property.read().toString();
        else
          value = '"' + property.read().toString().replace('"', '\'') + '"'; // Replace quotes in rich text
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
        value += indentStep + "]"; // close list
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

    value += QString(objectInfo->className()) + " {\n"; // open object
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

    Q_FOREACH(const QString &currentPropertyName, properties)
    {
        QDeclarativeProperty currentProperty(const_cast<PQBaseItem *>(this), currentPropertyName);
        outStream << serializeProperty(currentProperty, indentSize, indentStep);
    }

    // Close self declaration
    --indentSize;
    outStream << indentStep.repeated(indentSize) << '}' << endl;

    return output;
}
