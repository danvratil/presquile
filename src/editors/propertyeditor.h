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

#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QObject>
#include <QPointer>
#include <QMetaProperty>

class QDialog;
class PropertyEditor : public QObject
{
    Q_OBJECT

  public:
    PropertyEditor(QObject *object, const QString &propertyName, QObject *parent = 0);
    virtual ~PropertyEditor();

  public Q_SLOTS:
    int exec();

  private Q_SLOTS:
    void slotColorDialogAccepted();
    void slotFileDialogAccepted();
    void slotTextEditorChanged();

  private:
    QDialog* getDialog() const;

    QPointer<QObject> mObject;
    QString mPropertyName;
    QMetaProperty mMetaProperty;
};

#endif // PROPERTYEDITOR_H
