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

#include "transformationseditor.h"
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QDeclarativeListProperty>
#include <qdeclarativeitem.h>
#include <QGraphicsTransform>
#include <QVector2D>

#include <QDebug>

TransformationsEditor::TransformationsEditor(QWidget* parent)
    : QTabWidget(parent)
    , mObject(0)
{
    mRotationTab = new QWidget(this);
    QFormLayout *layout = new QFormLayout(mRotationTab);

    mRotationAngle = new QDoubleSpinBox(this);
    mRotationAngle->setMinimum(LONG_MIN);
    mRotationAngle->setMaximum(LONG_MAX);
    layout->addRow(tr("Angle"), mRotationAngle);
    connect(mRotationAngle, SIGNAL(valueChanged(double)), SLOT(slotRotationAngleEditValueChanged()));

    mRotationXAxis = new QDoubleSpinBox(this);
    mRotationXAxis->setMinimum(LONG_MIN);
    mRotationXAxis->setMaximum(LONG_MAX);
    layout->addRow(tr("X Axis"), mRotationXAxis);
    connect(mRotationXAxis, SIGNAL(valueChanged(double)), SLOT(slotRotationAxisEditValueChanged()));

    mRotationYAxis = new QDoubleSpinBox(this);
    mRotationYAxis->setMinimum(LONG_MIN);
    mRotationYAxis->setMaximum(LONG_MAX);
    layout->addRow(tr("Y Axis"), mRotationYAxis);
    connect(mRotationYAxis, SIGNAL(valueChanged(double)), SLOT(slotRotationAxisEditValueChanged()));

    mRotationZAxis = new QDoubleSpinBox(this);
    mRotationZAxis->setMinimum(LONG_MIN);
    mRotationZAxis->setMaximum(LONG_MAX);
    layout->addRow(tr("Z Axis"), mRotationZAxis);
    connect(mRotationZAxis, SIGNAL(valueChanged(double)), SLOT(slotRotationAxisEditValueChanged()));

    mRotationXOrigin = new QDoubleSpinBox(this);
    mRotationXOrigin->setMinimum(LONG_MIN);
    mRotationXOrigin->setMaximum(LONG_MAX);
    layout->addRow(tr("X Origin"), mRotationXOrigin);
    connect(mRotationXOrigin, SIGNAL(valueChanged(double)), SLOT(slotRotationOriginEditValueChanged()));

    mRotationYOrigin = new QDoubleSpinBox(this);
    mRotationYOrigin->setMinimum(LONG_MIN);
    mRotationYOrigin->setMaximum(LONG_MAX);
    layout->addRow(tr("Y Origin"), mRotationYOrigin);
    connect(mRotationYOrigin, SIGNAL(valueChanged(double)), SLOT(slotRotationOriginEditValueChanged()));


    mScaleTab = new QWidget(this);
    layout = new QFormLayout(mScaleTab);

    mScaleXOrigin = new QDoubleSpinBox(this);
    mScaleXOrigin->setMinimum(LONG_MIN);
    mScaleXOrigin->setMaximum(LONG_MAX);
    layout->addRow(tr("X Origin"), mScaleXOrigin);
    connect(mScaleXOrigin, SIGNAL(valueChanged(double)), SLOT(slotScaleOriginEditValueChanged()));

    mScaleYOrigin = new QDoubleSpinBox(this);
    mScaleYOrigin->setMinimum(LONG_MIN);
    mScaleYOrigin->setMaximum(LONG_MAX);
    layout->addRow(tr("Y Origin"), mScaleYOrigin);
    connect(mScaleYOrigin, SIGNAL(valueChanged(double)), SLOT(slotScaleOriginEditValueChanged()));

    mScaleXScale = new QDoubleSpinBox(this);
    mScaleXScale->setMinimum(LONG_MIN);
    mScaleXScale->setMaximum(LONG_MAX);
    mScaleXScale->setSingleStep(0.1);
    layout->addRow(tr("X Scale"), mScaleXScale);
    connect(mScaleXScale, SIGNAL(valueChanged(double)), SLOT(slotScaleScaleEditValueChanged()));

    mScaleYScale = new QDoubleSpinBox(this);
    mScaleYScale->setMinimum(LONG_MIN);
    mScaleYScale->setMaximum(LONG_MAX);
    mScaleYScale->setSingleStep(0.1);
    layout->addRow(tr("Y Scale"), mScaleYScale);
    connect(mScaleYScale, SIGNAL(valueChanged(double)), SLOT(slotScaleScaleEditValueChanged()));


    mTranslateTab = new QWidget(this);
    layout = new QFormLayout(mTranslateTab);

    mTranslateX = new QDoubleSpinBox(this);
    mTranslateX->setMinimum(LONG_MIN);
    mTranslateX->setMaximum(LONG_MAX);
    layout->addRow(tr("X"), mTranslateX);
    connect(mTranslateX, SIGNAL(valueChanged(double)), SLOT(slotTranslateEditValueChanged()));

    mTranslateY = new QDoubleSpinBox(this);
    mTranslateY->setMinimum(LONG_MIN);
    mTranslateY->setMaximum(LONG_MAX);
    layout->addRow(tr("Y"), mTranslateY);
    connect(mTranslateY, SIGNAL(valueChanged(double)), SLOT(slotTranslateEditValueChanged()));

    addTab(mRotationTab, tr("Rotation"));
    addTab(mScaleTab, tr("Scale"));
    addTab(mTranslateTab, tr("Translate"));
}

TransformationsEditor::~TransformationsEditor()
{

}

QGraphicsRotation* TransformationsEditor::rotationTransformation() const
{
    if (mObject == 0) {
	return 0;
    }

    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(mObject);
    if (!item) {
	return 0;
    }

    QList<QGraphicsTransform*> transformations = item->transformations();
    for (int ii = 0; ii < transformations.count(); ii++) {
	QGraphicsTransform *transformation = transformations.at(ii);

	if (qobject_cast<QGraphicsRotation*>(transformation) != 0) {
	    return qobject_cast<QGraphicsRotation*>(transformation);
	}
    }

    return 0;
}

QGraphicsScale* TransformationsEditor::scaleTransformation() const
{
    if (mObject == 0) {
	return 0;
    }

    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(mObject);
    if (!item) {
	return 0;
    }

    QList<QGraphicsTransform*> transformations = item->transformations();
    for (int ii = 0; ii < transformations.count(); ii++) {
	QGraphicsTransform *transformation = transformations.at(ii);

	if (qobject_cast<QGraphicsScale*>(transformation) != 0) {
	    return qobject_cast<QGraphicsScale*>(transformation);
	}
    }

    return 0;
}

QGraphicsTransform* TransformationsEditor::translationTransformation() const
{
    if (mObject == 0) {
	return 0;
    }

    QDeclarativeItem *item = qobject_cast<QDeclarativeItem*>(mObject);
    if (!item) {
	return 0;
    }

    QList<QGraphicsTransform*> transformations = item->transformations();
    for (int ii = 0; ii < transformations.count(); ii++) {
	QGraphicsTransform *transformation = transformations.at(ii);

	if ((qobject_cast<QGraphicsRotation*>(transformation) == 0) &&
	    (qobject_cast<QGraphicsScale*>(transformation)) == 0) {
	    return qobject_cast<QGraphicsTransform*>(transformation);
	}
    }

    return 0;
}


void TransformationsEditor::setObject(QObject *object)
{
    mObject = object;
    disconnect(this, SLOT(slotRotationAngleChanged()));
    disconnect(this, SLOT(slotRotationAxisChanged()));
    disconnect(this, SLOT(slotRotationOriginChanged()));
    disconnect(this, SLOT(slotScaleOriginChanged()));
    disconnect(this, SLOT(slotScaleScaleChanged()));

    QGraphicsRotation *rotation = rotationTransformation();
    connect(rotation, SIGNAL(angleChanged()), SLOT(slotRotationAngleChanged()));
    connect(rotation, SIGNAL(axisChanged()), SLOT(slotRotationAxisChanged()));
    connect(rotation, SIGNAL(originChanged()), SLOT(slotRotationOriginChanged()));
    slotRotationAngleChanged();
    slotRotationAxisChanged();
    slotRotationOriginChanged();

    QGraphicsScale *scale = scaleTransformation();
    connect(scale, SIGNAL(originChanged()), SLOT(slotScaleOriginChanged()));
    connect(scale, SIGNAL(scaleChanged()), SLOT(slotScaleScaleChanged()));
    slotScaleOriginChanged();
    slotScaleScaleChanged();

    QGraphicsTransform *translation = translationTransformation();
    mTranslateX->setValue(translation->property("x").toReal());
    mTranslateY->setValue(translation->property("y").toReal());
}

void TransformationsEditor::slotRotationAngleChanged()
{
    QGraphicsRotation *rotation = rotationTransformation();
    if (rotation) {
	mRotationAngle->setValue(rotation->angle());
    }
}

void TransformationsEditor::slotRotationAxisChanged()
{
    QGraphicsRotation *rotation = rotationTransformation();
    if (rotation) {
	mRotationXAxis->setValue(rotation->axis().x());
	mRotationYAxis->setValue(rotation->axis().y());
	mRotationZAxis->setValue(rotation->axis().z());
    }
}

void TransformationsEditor::slotRotationOriginChanged()
{
    QGraphicsRotation *rotation = rotationTransformation();
    if (rotation) {
	mRotationXOrigin->setValue(rotation->origin().x());
	mRotationYOrigin->setValue(rotation->origin().y());
    }
}

void TransformationsEditor::slotScaleScaleChanged()
{
    QGraphicsScale *scale = scaleTransformation();
    if (scale) {
	mScaleXScale->setValue(scale->xScale());
	mScaleYScale->setValue(scale->yScale());
    }
}

void TransformationsEditor::slotScaleOriginChanged()
{
    QGraphicsScale *scale = scaleTransformation();
    if (scale) {
	mScaleXOrigin->setValue(scale->origin().x());
	mScaleYOrigin->setValue(scale->origin().y());
    }
}

void TransformationsEditor::slotRotationAngleEditValueChanged()
{
    QGraphicsRotation *rotation = rotationTransformation();
    if (rotation) {
	rotation->setAngle(mRotationAngle->value());
    }
}

void TransformationsEditor::slotRotationAxisEditValueChanged()
{
    QGraphicsRotation *rotation = rotationTransformation();
    if (rotation) {
	QVector3D vector(mRotationXAxis->value(), mRotationYAxis->value(), mRotationZAxis->value());
	rotation->setAxis(vector);
    }
}

void TransformationsEditor::slotRotationOriginEditValueChanged()
{
    QGraphicsRotation *rotation = rotationTransformation();
    if (rotation) {
	QVector2D vector(mRotationXOrigin->value(), mRotationYOrigin->value());
	rotation->setOrigin(vector);
    }
}

void TransformationsEditor::slotScaleOriginEditValueChanged()
{
    QGraphicsScale *scale = scaleTransformation();
    if (scale) {
	QVector3D vector(mScaleXOrigin->value(), mScaleYOrigin->value(), 0);
	scale->setOrigin(vector);
    }
}

void TransformationsEditor::slotScaleScaleEditValueChanged()
{
    QGraphicsScale *scale = scaleTransformation();
    if (scale) {
	scale->setXScale(mScaleXScale->value());
	scale->setYScale(mScaleYScale->value());
    }
}

void TransformationsEditor::slotTranslateEditValueChanged()
{
    QGraphicsTransform *translation = translationTransformation();
    if (translation) {
	translation->setProperty("x", mTranslateX->value());
	translation->setProperty("y", mTranslateY->value());
    }
}



#include "transformationseditor.moc"