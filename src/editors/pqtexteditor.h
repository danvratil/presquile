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

#ifndef PQTEXTEDITOR_H
#define PQTEXTEDITOR_H

#include <QMainWindow>
#include <QMap>
#include <QTextCharFormat>

class QFontComboBox;
class QComboBox;
class QGridLayout;
class QTextEdit;
class QAction;
class QToolBar;

class PQTextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit PQTextEditor(QWidget* parent = 0);
    virtual ~PQTextEditor();

    void setText(const QString &text);
    QString html() const;
    QString plainText() const;

private Q_SLOTS:
    void slotToggleBold();
    void slotToggleItalic();
    void slotToggleStrikethrough();
    void slotToggleUnderline();
    void slotJustifyLeft();
    void slotJustifyCenter();
    void slotJustifyFill();
    void slotJustifyRight();
    void slotIndent();
    void slotUnindent();
    void slotChangeStyle(int index);
    void slotChangeFont(const QFont &font);
    void slotChangeFontSize(int index);
    void slotChangeColor();

Q_SIGNALS:
    void textChanged();

private:
    QAction* addAction(QToolBar *toolbar, const QString &name, const QString &icon,
		       const QString &text, bool checkable, const QKeySequence &shortcut,
		       const QObject *receiver, const char *member);
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);

    QGridLayout *mLayout;

    QTextEdit *mEditor;
    QMap<QString, QAction*> mActions;

    QComboBox *mStyleComboBox;
    QFontComboBox *mFontComboBox;
    QComboBox *mFontSizeComboBox;
};

#endif // PQTEXTEDITOR_H
