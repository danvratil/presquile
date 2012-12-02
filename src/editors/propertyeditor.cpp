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

#include "propertyeditor.h"

#include <QDialog>

#include <QColorDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QUrl>
#include <QDebug>

#include "../pqtexteditor.h"

PropertyEditor::PropertyEditor(QObject* object, const QString& propertyName, QObject* parent):
    QObject(parent),
    mObject(object),
    mPropertyName(propertyName)
{
    const QMetaObject *metaObject = mObject->metaObject();
    const int index = metaObject->indexOfProperty(mPropertyName.toLatin1().constData());
    mMetaProperty = metaObject->property(index);
}

PropertyEditor::~PropertyEditor()
{

}

int PropertyEditor::exec()
{
    QPointer<QDialog> dlg = getDialog();
    if (dlg.isNull()) {
	return -1;
    }

    int result = dlg->exec();

    delete dlg;

    return result;
}

QDialog* PropertyEditor::getDialog() const
{
    if (!mMetaProperty.isValid()) {
	return 0;
    }

    if (mMetaProperty.type() == QVariant::Color) {
	QColorDialog *dialog = new QColorDialog();
	dialog->setCurrentColor(QColor(mMetaProperty.read(mObject).value<QColor>()));
	connect(dialog, SIGNAL(accepted()), SLOT(slotColorDialogAccepted()));
	return dialog;

    } else if (mMetaProperty.type() == QVariant::String) {
	QDialog *dialog = new QDialog();
        QVBoxLayout *layout = new QVBoxLayout(dialog);
	PQTextEditor *editor = new PQTextEditor();
        layout->addWidget(editor);
	editor->setText(mMetaProperty.read(mObject).toString());
	connect(editor, SIGNAL(textChanged()), SLOT(slotTextEditorChanged()));
        editor->setParent(dialog);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(dialog);
        buttonBox->addButton(QDialogButtonBox::Ok);
        connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
        layout->addWidget(buttonBox);
	return dialog;

    } else if (mMetaProperty.type() == QVariant::Url) {
	QFileDialog *dialog = new QFileDialog();
	dialog->setAcceptMode(QFileDialog::AcceptOpen);
	connect(dialog, SIGNAL(accepted()), SLOT(slotFileDialogAccepted()));
	return dialog;

    }

    return 0;
}

void PropertyEditor::slotColorDialogAccepted()
{
    QColorDialog *dialog = qobject_cast<QColorDialog*>(sender());
    mMetaProperty.write(mObject, dialog->currentColor());
}

void PropertyEditor::slotFileDialogAccepted()
{
    QFileDialog *dialog = qobject_cast<QFileDialog*>(sender());
    QStringList files = dialog->selectedFiles();
    if (files.isEmpty()) {
	return;
    }

    mMetaProperty.write(mObject, QUrl::fromLocalFile(files.first()));
}

void PropertyEditor::slotTextEditorChanged()
{
    PQTextEditor *editor = qobject_cast<PQTextEditor*>(sender());
    mMetaProperty.write(mObject, editor->html());
}


#include "propertyeditor.moc"