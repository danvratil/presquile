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

#include "propertieseditor.h"
#include "easingcurveeditor.h"
#include "propertieseditoritem.h"

#include <QMetaProperty>

#include <QDebug>

Q_DECLARE_METATYPE(QSharedPointer<QObject>);
Q_DECLARE_METATYPE(QMetaProperty);

static const QList<QVariant::Type> supportedTypes = QList<QVariant::Type>()
							<< QVariant::Bool
							<< QVariant::Color
							<< QVariant::Double
							<< QVariant::EasingCurve
							<< QVariant::Font
							<< QVariant::Int
							<< QVariant::LongLong
							<< QVariant::String
							<< QVariant::ULongLong
							<< QVariant::UInt;

PropertiesEditor::PropertiesEditor(QWidget* parent)
  : QTableWidget(parent)
  , mObject(0)
{
    setColumnCount(2);
    setSelectionBehavior(SelectRows);
    setAlternatingRowColors(true);
    sortByColumn(0, Qt::AscendingOrder);
    setSortingEnabled(true);

    setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Property")));
    setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Value")));
}

PropertiesEditor::~PropertiesEditor()
{

}

void PropertiesEditor::setObject(const QSharedPointer< QObject >& object)
{
    clear();
    setRowCount(0);

    setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Property")));
    setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Value")));

    mObject = object;
    if (mObject.isNull()) {
	return;
    }

    setSortingEnabled(false);

    QStringList properties;
    const QMetaObject *metaObject = mObject->metaObject();
    int pIndex = metaObject->indexOfProperty("_PQProperties");
    if (pIndex > -1) {
	QMetaProperty p = metaObject->property(pIndex);
	properties = p.read(mObject.data()).toStringList();
    }

    qDebug() << metaObject->superClass()->className();

    QStringList processed;
    int count = metaObject->propertyCount();
    while (metaObject) {
	for (int ii = 0; ii < count; ii++) {
	    QMetaProperty property = metaObject->property(ii);

	    if (processed.contains(property.name())) {
		continue;
	    }

	    /* If the properties list is not empty, then accept only properties
	    * from that list. */
	    if (!properties.isEmpty() && !properties.contains(property.name())) {
		continue;
	    }

	    /* Don't display our internal properties or properties we can't edit */
	    if (QString(property.name()).startsWith(QLatin1String("_PQ")) ||
		!supportedTypes.contains(property.type())) {
		continue;
	    }

	    int row = rowCount();
	    setRowCount(rowCount() + 1);
	    setVerticalHeaderItem(row, new QTableWidgetItem(QString()));

	    QTableWidgetItem *propertyNameItem = new QTableWidgetItem;
	    propertyNameItem->setText(property.name());
	    propertyNameItem->setData(PropertyIndexRole, ii);
	    propertyNameItem->setFlags(propertyNameItem->flags() ^ Qt::ItemIsEditable);
	    setItem(row, 0, propertyNameItem);

	    PropertiesEditorItem *propertyValueItem = new PropertiesEditorItem(mObject, property, this);
	    if (!property.isWritable()) {
		propertyValueItem->setFlags(propertyValueItem->flags() ^ Qt::ItemIsEditable);
	    }
	    setItem(row, 1, propertyValueItem);

	    setEditorWidget(row);

	    processed << property.name();
	}

	metaObject = metaObject->superClass();
    }

    setSortingEnabled(true);
}

QSharedPointer< QObject > PropertiesEditor::object() const
{
    return mObject;
}

void PropertiesEditor::setEditorWidget(int row)
{
    PropertiesEditorItem *editorItem = dynamic_cast<PropertiesEditorItem*>(item(row, 1));

    setCellWidget(row, 1, editorItem->editorWidget());
}

QMetaProperty PropertiesEditor::property(int row)
{
    if (row < 0) {
	return QMetaProperty();
    }

    int index = item(row, 0)->data(PropertyIndexRole).toInt();
    const QMetaObject *metaObject = mObject->metaObject();

    return metaObject->property(index);
}

#include "propertieseditor.moc"