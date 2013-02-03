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

#include "easingcurveeditor.h"

#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <QGraphicsView>
#include <QTimer>
#include <QGraphicsPathItem>
#include <QMetaEnum>

EasingCurveEditor::EasingCurveEditor(QWidget* parent)
    : QDialog(parent)
    , mPathItem(0)
{
    mPaintTimer = new QTimer(this);

    mLayout = new QGridLayout(this);
    setLayout(mLayout);

    QLabel *label = new QLabel(tr("Type:"), this);
    mLayout->addWidget(label, 0, 0);

    mTypeCombo = new QComboBox(this);
    mTypeCombo->setEditable(false);
    label->setBuddy(mTypeCombo);
    mLayout->addWidget(mTypeCombo, 0, 1);
    connect(mTypeCombo, SIGNAL(currentIndexChanged(int)), SLOT(slotCurveTypeChanged()));

    label = new QLabel(tr("Amplitude:"), this);
    mLayout->addWidget(label, 1, 0);

    mAmplitudeSpinBox = new QDoubleSpinBox(this);
    mAmplitudeSpinBox->setSingleStep(0.01);
    mAmplitudeSpinBox->setMinimum( - mAmplitudeSpinBox->maximum());
    label->setBuddy(mAmplitudeSpinBox);
    mLayout->addWidget(mAmplitudeSpinBox, 1, 1);
    connect(mAmplitudeSpinBox, SIGNAL(valueChanged(double)), SLOT(slotPropertyChanged()));

    label = new QLabel(tr("Overshoot:"), this);
    mLayout->addWidget(label, 2, 0);

    mOvershootSpinBox = new QDoubleSpinBox(this);
    mOvershootSpinBox->setSingleStep(0.01);
    mOvershootSpinBox->setMinimum( - mOvershootSpinBox->maximum());
    label->setBuddy(mOvershootSpinBox);
    mLayout->addWidget(mOvershootSpinBox, 2, 1);
    connect(mOvershootSpinBox, SIGNAL(valueChanged(double)), SLOT(slotPropertyChanged()));

    label = new QLabel(tr("Period:"), this);
    mLayout->addWidget(label, 3, 0);

    mPeriodSpinBox = new QDoubleSpinBox(this);
    mPeriodSpinBox->setSingleStep(0.01);
    mPeriodSpinBox->setMinimum( - mPeriodSpinBox->maximum());
    label->setBuddy(mPeriodSpinBox);
    mLayout->addWidget(mPeriodSpinBox, 3, 1);
    connect(mPeriodSpinBox, SIGNAL(valueChanged(double)), SLOT(slotPropertyChanged()));

    mButtonBox = new QDialogButtonBox(this);
    mButtonBox->addButton(QDialogButtonBox::Ok);
    mButtonBox->addButton(QDialogButtonBox::Cancel);
    connect(mButtonBox, SIGNAL(accepted()), SLOT(accept()));
    connect(mButtonBox, SIGNAL(rejected()), SLOT(reject()));
    mLayout->addWidget(mButtonBox, 5, 0, 1, 4, Qt::AlignRight);

    mScene = new QGraphicsScene(this);

    label = new QLabel(tr("Preview:"), this);
    mLayout->addWidget(label, 0, 3);

    mGraphicsView = new QGraphicsView(mScene, this);
    mGraphicsView->setMinimumSize(250, 250);
    mGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mLayout->addWidget(mGraphicsView, 1, 3, 3, 1);

    /* There's only one enum */
    /* FIXME: We should be more careful, there might be more added in future */
    QMetaEnum metaEnum = QEasingCurve::staticMetaObject.enumerator(0);
    for (int ii = 0; ii < metaEnum.keyCount(); ii++) {
        /* We don't support custom easing curves yet */
        if ((metaEnum.value(ii) == QEasingCurve::Custom) ||
            (metaEnum.value(ii) == QEasingCurve::NCurveTypes)) {
              continue;
        }

        mTypeCombo->addItem(metaEnum.key(ii), metaEnum.value(ii));
    }
    mTypeCombo->model()->sort(0, Qt::AscendingOrder);


    initScene();
}

EasingCurveEditor::~EasingCurveEditor()
{
}

void EasingCurveEditor::initScene()
{
    mScene->setSceneRect(0, 0, 250, 250);
    QPen fullPen(palette().light().color());
    fullPen.setStyle(Qt::SolidLine);
    mScene->addLine(20, 220, 220, 220, fullPen);
    mScene->addLine(30, 30, 30, 230, fullPen);
    QFont textFont = font();
    textFont.setPixelSize(9);
    QGraphicsTextItem *text = mScene->addText(QLatin1String("[0,0]"), textFont);
    text->setPos(0, 220);

    text = mScene->addText(QLatin1String("[1,1]"), textFont);
    text->setPos(220, 5);

    QPen dottedPen(palette().light().color());
    dottedPen.setStyle(Qt::DotLine);
    mScene->addLine(30, 30, 220, 30, dottedPen);
    mScene->addLine(220, 30, 220, 220, dottedPen);
}

void EasingCurveEditor::slotCurveTypeChanged()
{
    QEasingCurve::Type type = (QEasingCurve::Type) mTypeCombo->itemData(mTypeCombo->currentIndex()).toInt();

    if ((type == QEasingCurve::InBounce) || (type == QEasingCurve::OutBounce) ||
        (type == QEasingCurve::InOutBounce) || (type == QEasingCurve::OutInBounce) ||
        (type == QEasingCurve::InElastic) || (type == QEasingCurve::OutElastic) ||
        (type == QEasingCurve::InOutElastic) || (type == QEasingCurve::OutInElastic)) {

        mAmplitudeSpinBox->setEnabled(true);
    } else {
        mAmplitudeSpinBox->setEnabled(false);
    }

    if ((type == QEasingCurve::InBack) || (type == QEasingCurve::OutBack) ||
        (type == QEasingCurve::InOutBack) || (type == QEasingCurve::OutInBack)) {

        mOvershootSpinBox->setEnabled(true);
    } else {
        mOvershootSpinBox->setEnabled(false);
    }

    if ((type == QEasingCurve::InElastic) || (type == QEasingCurve::OutElastic) ||
        (type == QEasingCurve::InOutElastic) || (type == QEasingCurve::OutInElastic)) {

        mPeriodSpinBox->setEnabled(true);
    } else {
        mPeriodSpinBox->setEnabled(false);
    }

    slotPropertyChanged();
}

void EasingCurveEditor::slotPropertyChanged()
{
    if (!mPaintTimer->isActive()) {
        mPaintTimer->singleShot(100, this, SLOT(slotPaintTimer()));
    }
}

void EasingCurveEditor::slotPaintTimer()
{
    QEasingCurve curve;
    curve.setType((QEasingCurve::Type) mTypeCombo->itemData(mTypeCombo->currentIndex()).toInt());
    curve.setAmplitude(mAmplitudeSpinBox->value());
    curve.setOvershoot(mOvershootSpinBox->value());
    curve.setPeriod(mPeriodSpinBox->value());

    QGraphicsPathItem *pathItem;
    QPainterPath path;

    path.moveTo(30, 220);
    for (qreal x = 0; x <= 1; x += 0.01) {
        qreal y = curve.valueForProgress(x);

        path.lineTo(30.0 + (190.0 * x), 220.0 - (190.0 * y));
    }
    pathItem = mScene->addPath(path, QPen(palette().text().color()));

    if (mPathItem) {
      mScene->removeItem(mPathItem);
      delete mPathItem;
    }

    mPathItem = pathItem;
}

void EasingCurveEditor::setEasingCurve(const QEasingCurve& curve)
{
    mCurve = curve;

    int row = mTypeCombo->findData(mCurve.type());
    mTypeCombo->setCurrentIndex(row);

    mAmplitudeSpinBox->setValue(mCurve.amplitude());
    mOvershootSpinBox->setValue(mCurve.overshoot());
    mPeriodSpinBox->setValue(mCurve.period());
}

QEasingCurve EasingCurveEditor::easingCurve() const
{
    return mCurve;
}

void EasingCurveEditor::accept()
{
    mCurve.setType((QEasingCurve::Type) mTypeCombo->itemData(mTypeCombo->currentIndex()).toInt());
    mCurve.setAmplitude(mAmplitudeSpinBox->value());
    mCurve.setOvershoot(mOvershootSpinBox->value());
    mCurve.setPeriod(mPeriodSpinBox->value());

    QDialog::accept();
}


#include "easingcurveeditor.moc"