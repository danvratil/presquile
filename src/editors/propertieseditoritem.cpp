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

#include "propertieseditoritem.h"
#include "easingcurveeditor.h"

#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QPushButton>
#include <QLineEdit>
#include <QFontComboBox>
#include <QStringBuilder>
#include <QColorDialog>

#include <QDebug>

#include <limits.h>

PropertiesEditorItem::PropertiesEditorItem(const QSharedPointer<QObject> &object, const QMetaProperty& property, QWidget *parent)
    : QObject(parent)
    , QTableWidgetItem()
    , mObject(object)
    , mProperty(property)
{
    if (mProperty.hasNotifySignal()) {
	QMetaMethod slot = metaObject()->method(metaObject()->indexOfMethod("slotPropertyValueChanged()"));
	QObject::connect(mObject.data(), mProperty.notifySignal(), (QObject*) this, slot);
    }

    prepareWidget();
}

PropertiesEditorItem::~PropertiesEditorItem()
{

}

QWidget* PropertiesEditorItem::editorWidget() const
{
    return mWidget;
}

QWidget* PropertiesEditorItem::parent() const
{
    return qobject_cast<QWidget*>(QObject::parent());
}

void PropertiesEditorItem::prepareWidget()
{
    QWidget *editor = 0;

    if (mProperty.type() == QVariant::BitArray) {

    } else if (mProperty.type() == QVariant::Bitmap) {

    } else if (mProperty.type() == QVariant::Bool) {
	QCheckBox *checkBox = new QCheckBox(parent());
	checkBox->setText(QString());
	checkBox->setChecked(mProperty.read(mObject.data()).toBool());
	editor = qobject_cast< QWidget* >(checkBox);
	connect(checkBox, SIGNAL(toggled(bool)), SLOT(slotCheckBoxToggled()));

    } else if (mProperty.type() == QVariant::Brush) {

    } else if (mProperty.type() == QVariant::ByteArray) {

    } else if (mProperty.type() == QVariant::Char) {

    } else if (mProperty.type() == QVariant::Color) {
	QPushButton *button = new QPushButton(parent());
	button->setText(mProperty.read(mObject.data()).value<QColor>().name());
	connect(button, SIGNAL(clicked(bool)), SLOT(slotOpenColorEditor()));
	editor = qobject_cast< QWidget* >(button);

    } else if (mProperty.type() == QVariant::Cursor) {

    } else if (mProperty.type() == QVariant::Date) {

    } else if (mProperty.type() == QVariant::DateTime) {

    } else if (mProperty.type() == QVariant::Double) {
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent());
	spinBox->setMaximum(LONG_MAX);
	spinBox->setMinimum(LONG_MIN);
	spinBox->setSingleStep(0.01);
	spinBox->setValue(mProperty.read(mObject.data()).toDouble());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(double)), SLOT(slotDoubleSpinBoxValueChanged()));

    } else if (mProperty.type() == QVariant::EasingCurve) {
	QPushButton *button = new QPushButton(parent());
	QEasingCurve curve = mProperty.read(mObject.data()).toEasingCurve();
	button->setText(curve.staticMetaObject.enumerator(0).valueToKey(curve.type()));
	connect(button, SIGNAL(clicked(bool)), SLOT(slotOpenEasingCurveEditor()));
	editor = qobject_cast< QWidget* >(button);

    } else if (mProperty.type() == QVariant::Font) {
	QFontComboBox *comboBox = new QFontComboBox(parent());
	comboBox->setCurrentFont(mProperty.read(mObject.data()).value<QFont>());
	editor = qobject_cast< QWidget* >(comboBox);
	connect(comboBox, SIGNAL(currentFontChanged(QFont)), SLOT(slotFontComboChanged()));

    } else if (mProperty.type() == QVariant::Hash) {

    } else if (mProperty.type() == QVariant::Icon) {

    } else if (mProperty.type() == QVariant::Image) {

    } else if (mProperty.type() == QVariant::Int) {
	QSpinBox *spinBox = new QSpinBox(parent());
	spinBox->setMinimum(INT_MIN);
	spinBox->setMaximum(INT_MAX);
	spinBox->setValue(mProperty.read(mObject.data()).toInt());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(int)), SLOT(slotSpinBoxValueChanged()));

    } else if (mProperty.type() == QVariant::KeySequence) {

    } else if (mProperty.type() == QVariant::Line) {

    } else if (mProperty.type() == QVariant::LineF) {

    } else if (mProperty.type() == QVariant::List) {

    } else if (mProperty.type() == QVariant::Locale) {

    } else if (mProperty.type() == QVariant::LongLong) {
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent());
	spinBox->setSingleStep(1.0);
	spinBox->setDecimals(0);
	spinBox->setMaximum(LONG_MAX);
	spinBox->setMinimum(LONG_MIN);
	spinBox->setValue(mProperty.read(mObject.data()).toLongLong());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(int)), SLOT(slotDoubleSpinBoxValueChanged()));

    } else if (mProperty.type() == QVariant::Map) {

    } else if (mProperty.type() == QVariant::Matrix) {

    } else if (mProperty.type() == QVariant::Matrix4x4) {

    } else if (mProperty.type() == QVariant::Palette) {

    } else if (mProperty.type() == QVariant::Pen) {

    } else if (mProperty.type() == QVariant::Pixmap) {

    } else if (mProperty.type() == QVariant::Point) {

    } else if (mProperty.type() == QVariant::PointF) {

    } else if (mProperty.type() == QVariant::Polygon) {

    } else if (mProperty.type() == QVariant::Quaternion) {

    } else if (mProperty.type() == QVariant::Rect) {

    } else if (mProperty.type() == QVariant::RectF) {

    } else if (mProperty.type() == QVariant::RegExp) {

    } else if (mProperty.type() == QVariant::Region) {

    } else if (mProperty.type() == QVariant::Size) {

    } else if (mProperty.type() == QVariant::SizeF) {

    } else if (mProperty.type() == QVariant::SizePolicy) {

    } else if (mProperty.type() == QVariant::String) {
	QLineEdit *lineEdit = new QLineEdit(parent());
	lineEdit->setText(mProperty.read(mObject.data()).toString());
	editor = qobject_cast< QWidget* >(lineEdit);
	connect(lineEdit, SIGNAL(textChanged(QString)), SLOT(slotLineEditChanged()));

    } else if (mProperty.type() == QVariant::StringList) {

    } else if (mProperty.type() == QVariant::TextFormat) {

    } else if (mProperty.type() == QVariant::TextLength) {

    } else if (mProperty.type() == QVariant::Time) {

    } else if (mProperty.type() == QVariant::Transform) {

    } else if (mProperty.type() == QVariant::UInt) {
	QSpinBox *spinBox = new QSpinBox(parent());
	spinBox->setMaximum(UINT_MAX);
	spinBox->setMinimum(0);
	spinBox->setValue(mProperty.read(mObject.data()).toUInt());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(int)), SLOT(slotSpinBoxValueChanged()));

    } else if (mProperty.type() == QVariant::ULongLong) {
	QDoubleSpinBox *spinBox = new QDoubleSpinBox(parent());
	spinBox->setSingleStep(1.0);
	spinBox->setDecimals(0);
	spinBox->setMinimum(0);
	spinBox->setMaximum(ULONG_MAX);
	spinBox->setValue(mProperty.read(mObject.data()).toULongLong());
	editor = qobject_cast< QWidget* >(spinBox);
	connect(spinBox, SIGNAL(valueChanged(int)), SLOT(slotDoubleSpinBoxValueChanged()));

    } else if (mProperty.type() == QVariant::Url) {
	QLineEdit *lineEdit = new QLineEdit(parent());
	lineEdit->setText(mProperty.read(mObject.data()).toString());
	editor = qobject_cast< QWidget* >(lineEdit);
	connect(lineEdit, SIGNAL(textChanged(QString)), SLOT(slotLineEditChanged()));

    } else if (mProperty.type() == QVariant::UserType) {

    } else if (mProperty.type() == QVariant::Vector2D) {

    } else if (mProperty.type() == QVariant::Vector3D) {

    } else if (mProperty.type() == QVariant::Vector4D) {

    }

    mWidget = editor;
}

void PropertiesEditorItem::slotOpenEasingCurveEditor()
{
    EasingCurveEditor *editor = new EasingCurveEditor(parent());
    editor->setEasingCurve(mProperty.read(mObject.data()).toEasingCurve());
    if (editor->exec() == QDialog::Accepted) {
	QEasingCurve curve = editor->easingCurve();
	mProperty.write(mObject.data(), curve);

	QPushButton *button = qobject_cast<QPushButton*>(mWidget.data());
	button->setText(curve.staticMetaObject.enumerator(0).valueToKey(curve.type()));
    }

    delete editor;
}

void PropertiesEditorItem::slotOpenColorEditor()
{
    QColorDialog *dialog = new QColorDialog(parent());
    dialog->setCurrentColor(mProperty.read(mObject.data()).value<QColor>());
    if (dialog->exec() == QDialog::Accepted) {
	mProperty.write(mObject.data(), QVariant::fromValue(dialog->currentColor()));

	QPushButton *button = qobject_cast<QPushButton*>(mWidget.data());
	button->setText(dialog->currentColor().name());
    }

    delete dialog;
}

void PropertiesEditorItem::slotCheckBoxToggled()
{
    QCheckBox *checkBox = qobject_cast<QCheckBox*>(mWidget.data());
    mProperty.write(mObject.data(), checkBox->isChecked());
}

void PropertiesEditorItem::slotFontComboChanged()
{
    QFontComboBox *comboBox = qobject_cast<QFontComboBox*>(mWidget.data());
    mProperty.write(mObject.data(), comboBox->font());
}

void PropertiesEditorItem::slotLineEditChanged()
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(mWidget.data());
    mProperty.write(mObject.data(), lineEdit->text());
}

void PropertiesEditorItem::slotSpinBoxValueChanged()
{
    QSpinBox *spinBox = qobject_cast<QSpinBox*>(mWidget.data());
    mProperty.write(mObject.data(), spinBox->value());
}

void PropertiesEditorItem::slotDoubleSpinBoxValueChanged()
{
    QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(mWidget.data());
    mProperty.write(mObject.data(), spinBox->value());
}

void PropertiesEditorItem::slotPropertyValueChanged()
{
    if (mProperty.type() == QVariant::BitArray) {

    } else if (mProperty.type() == QVariant::Bitmap) {

    } else if (mProperty.type() == QVariant::Bool) {
	QCheckBox *checkBox = qobject_cast<QCheckBox*>(mWidget.data());
	checkBox->setChecked(mProperty.read(mObject.data()).toBool());

    } else if (mProperty.type() == QVariant::Brush) {

    } else if (mProperty.type() == QVariant::ByteArray) {

    } else if (mProperty.type() == QVariant::Char) {

    } else if (mProperty.type() == QVariant::Color) {

    } else if (mProperty.type() == QVariant::Cursor) {

    } else if (mProperty.type() == QVariant::Date) {

    } else if (mProperty.type() == QVariant::DateTime) {

    } else if (mProperty.type() == QVariant::Double) {
	QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(mWidget.data());
	spinBox->setValue(mProperty.read(mObject.data()).toDouble());

    } else if (mProperty.type() == QVariant::EasingCurve) {
	QPushButton *button = qobject_cast<QPushButton*>(mWidget.data());
	QEasingCurve curve = mProperty.read(mObject.data()).toEasingCurve();
	button->setText(curve.staticMetaObject.enumerator(0).valueToKey(curve.type()));

    } else if (mProperty.type() == QVariant::Font) {
	QFontComboBox *comboBox = qobject_cast<QFontComboBox*>(mWidget.data());
	comboBox->setCurrentFont(mProperty.read(mObject.data()).value<QFont>());

    } else if (mProperty.type() == QVariant::Hash) {

    } else if (mProperty.type() == QVariant::Icon) {

    } else if (mProperty.type() == QVariant::Image) {

    } else if (mProperty.type() == QVariant::Int) {
	QSpinBox *spinBox = qobject_cast<QSpinBox*>(mWidget.data());
	spinBox->setValue(mProperty.read(mObject.data()).toInt());

    } else if (mProperty.type() == QVariant::KeySequence) {

    } else if (mProperty.type() == QVariant::Line) {

    } else if (mProperty.type() == QVariant::LineF) {

    } else if (mProperty.type() == QVariant::List) {

    } else if (mProperty.type() == QVariant::Locale) {

    } else if (mProperty.type() == QVariant::LongLong) {
	QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(mWidget.data());
	spinBox->setValue(mProperty.read(mObject.data()).toLongLong());

    } else if (mProperty.type() == QVariant::Map) {

    } else if (mProperty.type() == QVariant::Matrix) {

    } else if (mProperty.type() == QVariant::Matrix4x4) {

    } else if (mProperty.type() == QVariant::Palette) {

    } else if (mProperty.type() == QVariant::Pen) {

    } else if (mProperty.type() == QVariant::Pixmap) {

    } else if (mProperty.type() == QVariant::Point) {

    } else if (mProperty.type() == QVariant::PointF) {

    } else if (mProperty.type() == QVariant::Polygon) {

    } else if (mProperty.type() == QVariant::Quaternion) {

    } else if (mProperty.type() == QVariant::Rect) {

    } else if (mProperty.type() == QVariant::RectF) {

    } else if (mProperty.type() == QVariant::RegExp) {

    } else if (mProperty.type() == QVariant::Region) {

    } else if (mProperty.type() == QVariant::Size) {

    } else if (mProperty.type() == QVariant::SizeF) {

    } else if (mProperty.type() == QVariant::SizePolicy) {

    } else if (mProperty.type() == QVariant::String) {
	QLineEdit *lineEdit = qobject_cast<QLineEdit*>(mWidget.data());
	lineEdit->setText(mProperty.read(mObject.data()).toString());

    } else if (mProperty.type() == QVariant::StringList) {

    } else if (mProperty.type() == QVariant::TextFormat) {

    } else if (mProperty.type() == QVariant::TextLength) {

    } else if (mProperty.type() == QVariant::Time) {

    } else if (mProperty.type() == QVariant::Transform) {

    } else if (mProperty.type() == QVariant::UInt) {
	QSpinBox *spinBox = qobject_cast<QSpinBox*>(mWidget.data());
	spinBox->setValue(mProperty.read(mObject.data()).toUInt());

    } else if (mProperty.type() == QVariant::ULongLong) {
	QDoubleSpinBox *spinBox = qobject_cast<QDoubleSpinBox*>(mWidget.data());
	spinBox->setValue(mProperty.read(mObject.data()).toULongLong());

    } else if (mProperty.type() == QVariant::Url) {
	QLineEdit *lineEdit = qobject_cast<QLineEdit*>(mWidget.data());
	lineEdit->setText(mProperty.read(mObject.data()).toString());

    } else if (mProperty.type() == QVariant::UserType) {

    } else if (mProperty.type() == QVariant::Vector2D) {

    } else if (mProperty.type() == QVariant::Vector3D) {

    } else if (mProperty.type() == QVariant::Vector4D) {

    }
}


#include "propertieseditoritem.moc"
