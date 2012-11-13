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

#include "pqmlrichtexteditor.h"

#include <QWidget>
#include <QGridLayout>
#include <QMainWindow>
#include <QToolBar>
#include <QTextEdit>
#include <QFontComboBox>
#include <QAction>

PQMLRichTextEditor::PQMLRichTextEditor(QWidget* parent):
    QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    mLayout = new QGridLayout(centralWidget);

    centralWidget->setLayout(mLayout);
    setCentralWidget(centralWidget);

    QAction *action;
    QToolBar *toolbar = addToolBar(tr("Edit Toolbar"));
    addAction(toolbar, QLatin1String("undo"), QLatin1String("edit-undo"), tr("Undo"), QKeySequence::Undo, mEditor, SLOT(undo()));
    addAction(toolbar, QLatin1String("redo"), QLatin1String("edit-redo"), tr("Redo"), QKeySequence::Redo, mEditor, SLOT(redo()));
    addAction(toolbar, QLatin1String("cut"), QLatin1String("edit-cut"), tr("Cut"), QKeySequence::Cut, mEditor, SLOT(cut()));
    addAction(toolbar, QLatin1String("copy"), QLatin1String("edit-copy"), tr("Copy"), QKeySequence::Copy, mEditor, SLOT(copy()));
    addAction(toolbar, QLatin1String("paste"), QLatin1String("edit-paste"), tr("Paste"), QKeySequence::Paste, mEditor, SLOT(paste()));

    toolbar = addToolBar(tr("Format Toolbar"));
    addAction(toolbar, QLatin1String("bold"), QLatin1String("format-text-bold"), tr("Bold"), QKeySequence::Bold, this, SLOT(slotToggleBold()));
    addAction(toolbar, QLatin1String("italic"), QLatin1String("format-text-italic"), tr("Italic"), QKeySequence::Italic, this, SLOT(slotToggleItalic()));
    addAction(toolbar, QLatin1String("strikethrough"), QLatin1String("format-text-strikethrough"), tr("Strikethrough"), QKeySequence(), this, SLOT(slotToggleStrikethrough()));
    addAction(toolbar, QLatin1String("underline"), QLatin1String("format-text-underline"), tr("Underline"), QKeySequence::Underline, this, SLOT(slotToggleUnderline()));
    toolbar->addSeparator();
    addAction(toolbar, QLatin1String("justify-left"), QLatin1String("format-justify-left"), tr("Justify Left"), QKeySequence(), this, SLOT(slotJustifyLeft()));
    addAction(toolbar, QLatin1String("justify-center"), QLatin1String("format-justify-center"), tr("Justify Center"), QKeySequence(), this, SLOT(slotJustifyCenter()));
    addAction(toolbar, QLatin1String("justify-fill"), QLatin1String("format-justify-fill"), tr("Justify Fill"), QKeySequence(), this, SLOT(slotJustifyFill()));
    addAction(toolbar, QLatin1String("justify-right"), QLatin1String("format-justify-right"), tr("Justify Right"), QKeySequence(), this, SLOT(slotJustifyRight()));
    toolbar->addSeparator();
    addAction(toolbar, QLatin1String("unindent"), QLatin1String("format-indent-less"), tr("Unindent"), QKeySequence(), this, SLOT(slotUnindent()));
    addAction(toolbar, QLatin1String("indent"), QLatin1String("format-indent-more"), tr("Indent"), QKeySequence(), this, SLOT(slotIndent()));

    toolbar = addToolBar(tr("Font Toolbar"));
    toolbar->addWidget(mStyleComboBox);
    toolbar->addWidget(mFontComboBox);
    toolbar->addWidget(mFontSizeComboBox);
}

PQMLRichTextEditor::~PQMLRichTextEditor()
{

}

QAction* PQMLRichTextEditor::addAction(QToolBar* toolbar, const QString& name, const QString& icon,
				       const QString& text, const QKeySequence& shortcut,
				       QObject* receiver, const char* member)
{
    QAction *action = toolbar->addAction(QIcon::fromTheme(icon), text, receiver, member);
    action->setShortcut(shortcut);
    mActions.insert(name, action);

    return action;
}


#include "pqmlrichtexteditor.moc"
