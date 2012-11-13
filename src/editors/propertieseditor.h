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

#ifndef PROPERTIESEDITOR_H
#define PROPERTIESEDITOR_H

#include <QTableWidget>
#include <QMetaProperty>

class PropertiesEditor : public QTableWidget
{
    Q_OBJECT

public:
    enum Roles {
	PropertyIndexRole = Qt::UserRole + 1,
    };

    explicit PropertiesEditor(QWidget* parent = 0);
    virtual ~PropertiesEditor();

    void setObject(const QSharedPointer<QObject> &object);
    QSharedPointer<QObject> object() const;

private Q_SLOTS:
    void slotOpenEasingCurveEditor();

    void slotSpinBoxValueChanged();
    void slotDoubleSpinBoxValueChanged();
    void slotCheckBoxToggled();
    void slotFontComboChanged();
    void slotLineEditChanged();

private:
    QMetaProperty property(int row);
    void setEditorWidget(int row);

    QSharedPointer<QObject> mObject;
};

#endif // PROPERTIESEDITOR_H
