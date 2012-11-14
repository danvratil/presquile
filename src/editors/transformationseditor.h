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

#ifndef TRANSFORMATIONSEDITOR_H
#define TRANSFORMATIONSEDITOR_H

#include <QTabWidget>

class QDoubleSpinBox;
class QTabWidget;

class QGraphicsTransform;
class QGraphicsScale;
class QGraphicsRotation;

class TransformationsEditor : public QTabWidget
{
  Q_OBJECT

public:
    explicit TransformationsEditor(QWidget* parent = 0);
    virtual ~TransformationsEditor();

public Q_SLOTS:
    void setObject(QObject *object);

private Q_SLOTS:
    void slotRotationAngleChanged();
    void slotRotationAxisChanged();
    void slotRotationOriginChanged();

    void slotScaleOriginChanged();
    void slotScaleScaleChanged();

    void slotRotationAngleEditValueChanged();
    void slotRotationAxisEditValueChanged();
    void slotRotationOriginEditValueChanged();

    void slotScaleOriginEditValueChanged();
    void slotScaleScaleEditValueChanged();

    void slotTranslateEditValueChanged();

private:
    QGraphicsRotation* rotationTransformation() const;
    QGraphicsScale* scaleTransformation() const;
    QGraphicsTransform* translationTransformation() const;

    QObject *mObject;

    QWidget *mRotationTab;
    QDoubleSpinBox *mRotationAngle;
    QDoubleSpinBox *mRotationXAxis;
    QDoubleSpinBox *mRotationYAxis;
    QDoubleSpinBox *mRotationZAxis;
    QDoubleSpinBox *mRotationXOrigin;
    QDoubleSpinBox *mRotationYOrigin;

    QWidget *mScaleTab;
    QDoubleSpinBox *mScaleXOrigin;
    QDoubleSpinBox *mScaleYOrigin;
    QDoubleSpinBox *mScaleXScale;
    QDoubleSpinBox *mScaleYScale;

    QWidget *mTranslateTab;
    QDoubleSpinBox *mTranslateX;
    QDoubleSpinBox *mTranslateY;
};

#endif // TRANSFORMATIONSEDITOR_H
