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

#ifndef PQMLRICHTEXTEDITOR_H
#define PQMLRICHTEXTEDITOR_H

#include <QMainWindow>
#include <QMap>

class QGridLayout;
class QTextEditor;
class QAction;
class QToolBar;

class PQMLRichTextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit PQMLRichTextEditor(QWidget* parent = 0);
    virtual ~PQMLRichTextEditor();

private:
    QAction* addAction(QToolBar *toolbar, const QString &name, const QString &icon,
		       const QString &text, const QKeySequence &shortcut,
		       QObject *receiver, const char *member);

    QGridLayout *mLayout;

    QTextEditor *mEditor;
    QMap<QString, QAction*> mActions;
};

#endif // PQMLRICHTEXTEDITOR_H
