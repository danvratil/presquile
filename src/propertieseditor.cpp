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
#include "editors/easingcurveeditor.h"

#include <QMetaProperty>

#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QFontComboBox>
#include <QPushButton>
#include <QEasingCurve>
#include <QDebug>

#include <limits.h>

Q_DECLARE_METATYPE(QSharedPointer<QObject>);
Q_DECLARE_METATYPE(QMetaProperty);

static const QList<QVariant::Type> supportedTypes = QList<QVariant::Type>()
							<< QVariant::Bool
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

    const QMetaObject *metaObject = mObject->metaObject();
    int count = metaObject->propertyCount();
    for (int ii = 0; ii < count; ii++) {
	QMetaProperty property = metaObject->property(ii);

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

	QTableWidgetItem *propertyValueItem = new QTableWidgetItem;
	if (!property.isWritable()) {
	    propertyValueItem->setFlags(propertyValueItem->flags() ^ Qt::ItemIsEditable);
	}
	setItem(row, 1, propertyValueItem);

	setEditorWidget(row);
    }

    setSortingEnabled(true);
}

QSharedPointer< QObject > PropertiesEditor::object() const
{
    return mObject;
}

void PropertiesEditor::setEditorWidget(int row)
{
    QMetaProperty metaProperty = property(row);

    QWidget *editor = 0;
    const QObject *instance = mObject.data();

    if (metaProperty.type() == QVariant::BitArray) {

    } else if (metaProperty.type() == QVariant::Bitmap) {

    } else if (metaProperty.type() == QVariant::Bool) {
	QCheckBox *checkBox = new QCheckBox(this);
	checkBox->setText(QString());
	checkBox->setChecked(metaProperty.read(instance).toBool());
	editor = qobject_cast< QWidget* >(checkBox);
	connect(checkBox, SIGNAL(toggled(bool)), SLOT(slotCheckBoxToggled()));

    } else if (metaProperty.type() == QVariant::Brush) {

    } else if (metaProperty.type() == QVariant::ByteArray) {

    } else if (metaProperty.type() == QVariant::Char) {

    } else if (metaProperty.type() == QVariant::Color) {

    } else if (metaProperty.type() == QVariant::Cursor) {

    } else if (metaProperty.type() == QVariant::Date) {

    } else if (metaProperty.type() == QVariant::DateTime) {

    } else if (metaProperty.type() == QVariant::Double) {
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
	spinBox->setMaximum(LONG_MAX);
	spinBox->setMinimum(LONG_MIN);
	spinBox->setValue(metaProperty.read(instance).toDouble());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(double)), SLOT(slotDoubleSpinBoxValueChanged()));

    } else if (metaProperty.type() == QVariant::EasingCurve) {
	QPushButton *button = new QPushButton(this);
	QEasingCurve curve = metaProperty.read(instance).toEasingCurve();
	button->setText(curve.staticMetaObject.enumerator(0).valueToKey(curve.type()));
	connect(button, SIGNAL(clicked(bool)), SLOT(slotOpenEasingCurveEditor()));
	editor = qobject_cast< QWidget* >(button);

    } else if (metaProperty.type() == QVariant::Font) {
	QFontComboBox *comboBox = new QFontComboBox(this);
	comboBox->setCurrentFont(metaProperty.read(instance).value<QFont>());
	editor = qobject_cast< QWidget* >(comboBox);
	connect(comboBox, SIGNAL(currentFontChanged(QFont)), SLOT(slotFontComboChanged()));

    } else if (metaProperty.type() == QVariant::Hash) {

    } else if (metaProperty.type() == QVariant::Icon) {

    } else if (metaProperty.type() == QVariant::Image) {

    } else if (metaProperty.type() == QVariant::Int) {
	QSpinBox *spinBox = new QSpinBox(this);
	spinBox->setMinimum(INT_MIN);
	spinBox->setMaximum(INT_MAX);
	spinBox->setValue(metaProperty.read(instance).toInt());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(int)), SLOT(slotSpinBoxValueChanged()));

    } else if (metaProperty.type() == QVariant::KeySequence) {

    } else if (metaProperty.type() == QVariant::Line) {

    } else if (metaProperty.type() == QVariant::LineF) {

    } else if (metaProperty.type() == QVariant::List) {

    } else if (metaProperty.type() == QVariant::Locale) {

    } else if (metaProperty.type() == QVariant::LongLong) {
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
	spinBox->setSingleStep(1.0);
	spinBox->setDecimals(0);
	spinBox->setMaximum(LONG_MAX);
	spinBox->setMinimum(LONG_MIN);
	spinBox->setValue(metaProperty.read(instance).toLongLong());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(int)), SLOT(slotDoubleSpinBoxValueChanged()));

    } else if (metaProperty.type() == QVariant::Map) {

    } else if (metaProperty.type() == QVariant::Matrix) {

    } else if (metaProperty.type() == QVariant::Matrix4x4) {

    } else if (metaProperty.type() == QVariant::Palette) {

    } else if (metaProperty.type() == QVariant::Pen) {

    } else if (metaProperty.type() == QVariant::Pixmap) {

    } else if (metaProperty.type() == QVariant::Point) {

    } else if (metaProperty.type() == QVariant::PointF) {

    } else if (metaProperty.type() == QVariant::Polygon) {

    } else if (metaProperty.type() == QVariant::Quaternion) {

    } else if (metaProperty.type() == QVariant::Rect) {

    } else if (metaProperty.type() == QVariant::RectF) {

    } else if (metaProperty.type() == QVariant::RegExp) {

    } else if (metaProperty.type() == QVariant::Region) {

    } else if (metaProperty.type() == QVariant::Size) {

    } else if (metaProperty.type() == QVariant::SizeF) {

    } else if (metaProperty.type() == QVariant::SizePolicy) {

    } else if (metaProperty.type() == QVariant::String) {
	QLineEdit *lineEdit = new QLineEdit(this);
	lineEdit->setText(metaProperty.read(instance).toString());
	editor = qobject_cast< QWidget* >(lineEdit);
	connect(lineEdit, SIGNAL(textChanged(QString)), SLOT(slotLineEditChanged()));

    } else if (metaProperty.type() == QVariant::StringList) {

    } else if (metaProperty.type() == QVariant::TextFormat) {

    } else if (metaProperty.type() == QVariant::TextLength) {

    } else if (metaProperty.type() == QVariant::Time) {

    } else if (metaProperty.type() == QVariant::Transform) {

    } else if (metaProperty.type() == QVariant::UInt) {
	QSpinBox *spinBox = new QSpinBox(this);
	spinBox->setMaximum(UINT_MAX);
	spinBox->setMinimum(0);
	spinBox->setValue(metaProperty.read(instance).toUInt());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(int)), SLOT(slotSpinBoxValueChanged()));

    } else if (metaProperty.type() == QVariant::ULongLong) {
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);
	spinBox->setSingleStep(1.0);
	spinBox->setDecimals(0);
	spinBox->setMinimum(0);
	spinBox->setMaximum(ULONG_MAX);
	spinBox->setValue(metaProperty.read(instance).toULongLong());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(int)), SLOT(slotDoubleSpinBoxValueChanged()));

    } else if (metaProperty.type() == QVariant::Url) {
	QLineEdit *lineEdit = new QLineEdit(this);
	lineEdit->setText(metaProperty.read(instance).toString());
	editor = qobject_cast< QWidget* >(lineEdit);
	connect(lineEdit, SIGNAL(textChanged(QString)), SLOT(slotLineEditChanged()));

    } else if (metaProperty.type() == QVariant::UserType) {

    } else if (metaProperty.type() == QVariant::Vector2D) {

    } else if (metaProperty.type() == QVariant::Vector3D) {

    } else if (metaProperty.type() == QVariant::Vector4D) {

    }

    if (editor) {
	editor->setProperty("row", row);
    }

    setCellWidget(row, 1, editor);
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

void PropertiesEditor::slotOpenEasingCurveEditor()
{
    QMetaProperty metaProperty = property(sender()->property("row").toInt());

    EasingCurveEditor *editor = new EasingCurveEditor(this);
    editor->setEasingCurve(metaProperty.read(mObject.data()).toEasingCurve());
    if (editor->exec() == QDialog::Accepted) {
	QEasingCurve curve = editor->easingCurve();
	metaProperty.write(mObject.data(), curve);

	QPushButton *button = qobject_cast<QPushButton*>(sender());
	button->setText(curve.staticMetaObject.enumerator(0).valueToKey(curve.type()));
    }
}

void PropertiesEditor::slotCheckBoxToggled()
{
    QMetaProperty metaProperty = property(sender()->property("row").toInt());
    QCheckBox *checkBox = qobject_cast<QCheckBox*>(sender());
    metaProperty.write(mObject.data(), checkBox->isChecked());
}

void PropertiesEditor::slotFontComboChanged()
{
    QMetaProperty metaProperty = property(sender()->property("row").toInt());
    QFontComboBox *comboBox = qobject_cast<QFontComboBox*>(sender());
    metaProperty.write(mObject.data(), comboBox->font());
}

void PropertiesEditor::slotLineEditChanged()
{
    QMetaProperty metaProperty = property(sender()->property("row").toInt());
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(sender());
    metaProperty.write(mObject.data(), lineEdit->text());
}

void PropertiesEditor::slotSpinBoxValueChanged()
{
    QMetaProperty metaProperty = property(sender()->property("row").toInt());
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(sender());
    metaProperty.write(mObject.data(), spinBox->value());
}

void PropertiesEditor::slotDoubleSpinBoxValueChanged()
{
    QMetaProperty metaProperty = property(sender()->property("row").toInt());
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(sender());
    metaProperty.write(mObject.data(), spinBox->value());
}






#include "propertieseditor.moc"