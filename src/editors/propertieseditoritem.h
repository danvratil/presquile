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

#ifndef PROPERTIESEDITORITEM_H
#define PROPERTIESEDITORITEM_H

#include <QTableWidget>
#include <QMetaProperty>
#include <QPointer>

class PropertiesEditorItemPrivate;

class PropertiesEditorItem : public QObject, public QTableWidgetItem
{
    Q_OBJECT

public:
    explicit PropertiesEditorItem(const QSharedPointer<QObject> &object, const QMetaProperty &property, QWidget *parent = 0);
    virtual ~PropertiesEditorItem();


    QWidget *editorWidget() const;

    QWidget *parent() const;

private Q_SLOTS:
    void slotPropertyValueChanged();

    void slotOpenEasingCurveEditor();
    void slotOpenColorEditor();

    void slotSpinBoxValueChanged();
    void slotDoubleSpinBoxValueChanged();
    void slotCheckBoxToggled();
    void slotFontComboChanged();
    void slotLineEditChanged();

private:
    void prepareWidget();

    QPointer<QWidget> mWidget;
    QSharedPointer<QObject> mObject;
    QMetaProperty mProperty;

};

#endif // PROPERTIESEDITORITEM_H
