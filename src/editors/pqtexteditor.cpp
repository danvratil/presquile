/*
 * Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
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

#include "pqtexteditor.h"

#include <QWidget>
#include <QGridLayout>
#include <QMainWindow>
#include <QToolBar>
#include <QTextEdit>
#include <QTextList>
#include <QFontComboBox>
#include <QAction>
#include <QApplication>
#include <QColorDialog>

PQTextEditor::PQTextEditor(QWidget* parent):
    QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    mLayout = new QGridLayout(centralWidget);
    centralWidget->setLayout(mLayout);

    setCentralWidget(centralWidget);

    mEditor = new QTextEdit(this);
    mLayout->addWidget(mEditor, 0, 0);
    connect(mEditor, SIGNAL(textChanged()), SIGNAL(textChanged()));

    QAction *action;
    QToolBar *toolbar = addToolBar(tr("Edit Toolbar"));
    addAction(toolbar, QLatin1String("undo"), QLatin1String("edit-undo"), tr("Undo"), false, QKeySequence::Undo, mEditor, SLOT(undo()));
    addAction(toolbar, QLatin1String("redo"), QLatin1String("edit-redo"), tr("Redo"), false, QKeySequence::Redo, mEditor, SLOT(redo()));
    addAction(toolbar, QLatin1String("cut"), QLatin1String("edit-cut"), tr("Cut"),  false,QKeySequence::Cut, mEditor, SLOT(cut()));
    addAction(toolbar, QLatin1String("copy"), QLatin1String("edit-copy"), tr("Copy"),  false,QKeySequence::Copy, mEditor, SLOT(copy()));
    addAction(toolbar, QLatin1String("paste"), QLatin1String("edit-paste"), tr("Paste"),  false,QKeySequence::Paste, mEditor, SLOT(paste()));

    toolbar = addToolBar(tr("Format Toolbar"));
    addAction(toolbar, QLatin1String("bold"), QLatin1String("format-text-bold"), tr("Bold"), true, QKeySequence::Bold, this, SLOT(slotToggleBold()));
    addAction(toolbar, QLatin1String("italic"), QLatin1String("format-text-italic"), tr("Italic"), true, QKeySequence::Italic, this, SLOT(slotToggleItalic()));
    addAction(toolbar, QLatin1String("strikethrough"), QLatin1String("format-text-strikethrough"), tr("Strikethrough"), true, QKeySequence(), this, SLOT(slotToggleStrikethrough()));
    addAction(toolbar, QLatin1String("underline"), QLatin1String("format-text-underline"), tr("Underline"), true, QKeySequence::Underline, this, SLOT(slotToggleUnderline()));
    toolbar->addSeparator();
    QActionGroup *group = new QActionGroup(this);
    group->addAction(addAction(toolbar, QLatin1String("justify-left"), QLatin1String("format-justify-left"), tr("Justify Left"), true, QKeySequence(), this, SLOT(slotJustifyLeft())));
    group->addAction(addAction(toolbar, QLatin1String("justify-center"), QLatin1String("format-justify-center"), tr("Justify Center"), true, QKeySequence(), this, SLOT(slotJustifyCenter())));
    group->addAction(addAction(toolbar, QLatin1String("justify-fill"), QLatin1String("format-justify-fill"), tr("Justify Fill"), true, QKeySequence(), this, SLOT(slotJustifyFill())));
    group->addAction(addAction(toolbar, QLatin1String("justify-right"), QLatin1String("format-justify-right"), tr("Justify Right"), true, QKeySequence(), this, SLOT(slotJustifyRight())));
    toolbar->addSeparator();
    addAction(toolbar, QLatin1String("unindent"), QLatin1String("format-indent-less"), tr("Unindent"), false, QKeySequence(), this, SLOT(slotUnindent()));
    addAction(toolbar, QLatin1String("indent"), QLatin1String("format-indent-more"), tr("Indent"), false, QKeySequence(), this, SLOT(slotIndent()));


    mStyleComboBox = new QComboBox(this);
    mStyleComboBox->addItem(tr("Standard"));
    mStyleComboBox->addItem(tr("Bullet List (Disc)"));
    mStyleComboBox->addItem(tr("Bullet List (Circle)"));
    mStyleComboBox->addItem(tr("Bullet List (Square)"));
    mStyleComboBox->addItem(tr("Ordered List (Decimal)"));
    mStyleComboBox->addItem(tr("Ordered List (Alpha lower)"));
    mStyleComboBox->addItem(tr("Ordered List (Alpha upper)"));
    mStyleComboBox->addItem(tr("Ordered List (Roman lower)"));
    mStyleComboBox->addItem(tr("Ordered List (Roman upper)"));
    connect(mStyleComboBox, SIGNAL(currentIndexChanged(int)), SLOT(slotChangeStyle(int)));

    mFontComboBox = new QFontComboBox(this);
    connect(mFontComboBox, SIGNAL(currentFontChanged(QFont)), SLOT(slotChangeFont(QFont)));

    mFontSizeComboBox = new QComboBox(this);
    QFontDatabase db;
    Q_FOREACH (int size, db.standardSizes()) {
        mFontSizeComboBox->addItem(QString::number(size));
    }
    /* Initialize */
    mFontSizeComboBox->setCurrentIndex(mFontSizeComboBox->findText(QString::number(QApplication::font().pointSize())));
    connect(mFontSizeComboBox, SIGNAL(currentIndexChanged(int)), SLOT(slotChangeFontSize(int)));

    QPixmap pixmap(16, 16);
    pixmap.fill(mEditor->textColor());
    QAction *colorAction = new QAction(pixmap, tr("Color"), this);
    connect(colorAction, SIGNAL(triggered(bool)), SLOT(slotChangeColor()));

    addToolBarBreak();
    toolbar = addToolBar(tr("Font Toolbar"));
    toolbar->addWidget(mStyleComboBox);
    toolbar->addWidget(mFontComboBox);
    toolbar->addWidget(mFontSizeComboBox);
    toolbar->addAction(colorAction);
}

PQTextEditor::~PQTextEditor()
{

}

QAction* PQTextEditor::addAction(QToolBar* toolbar, const QString& name, const QString& icon,
                                       const QString& text, bool checkable, const QKeySequence& shortcut,
                                       const QObject* receiver, const char* member)
{
    QAction *action = toolbar->addAction(QIcon::fromTheme(icon), text, receiver, member);
    action->setShortcut(shortcut);
    action->setCheckable(checkable);
    mActions.insert(name, action);

    return action;
}

void PQTextEditor::setText(const QString& text)
{
    mEditor->setText(text);
}

QString PQTextEditor::html() const
{
    return mEditor->toHtml();
}

QString PQTextEditor::plainText() const
{
    return mEditor->toPlainText();
}

void PQTextEditor::slotToggleBold()
{
    QTextCharFormat format;
    format.setFontWeight(mActions.value(QLatin1String("bold"))->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(format);
}

void PQTextEditor::slotToggleItalic()
{
    QTextCharFormat format;
    format.setFontItalic(mActions.value(QLatin1String("italic"))->isChecked());
    mergeFormatOnWordOrSelection(format);
}

void PQTextEditor::slotToggleStrikethrough()
{
    QTextCharFormat format;
    format.setFontStrikeOut(mActions.value(QLatin1String("strikethrough"))->isChecked());
    mergeFormatOnWordOrSelection(format);
}

void PQTextEditor::slotToggleUnderline()
{
    QTextCharFormat format;
    format.setFontUnderline(mActions.value(QLatin1String("underline"))->isChecked());
    mergeFormatOnWordOrSelection(format);
}

void PQTextEditor::slotIndent()
{
    QTextBlockFormat format = mEditor->textCursor().blockFormat();
    format.setIndent(format.indent() + 1);
}

void PQTextEditor::slotUnindent()
{
    QTextBlockFormat format = mEditor->textCursor().blockFormat();
    if (format.indent() > 0) {
        format.setIndent(format.indent() - 1);
    }
}

void PQTextEditor::slotJustifyLeft()
{
    mEditor->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
}

void PQTextEditor::slotJustifyCenter()
{
    mEditor->setAlignment(Qt::AlignHCenter);
}

void PQTextEditor::slotJustifyFill()
{
    mEditor->setAlignment(Qt::AlignJustify);
}

void PQTextEditor::slotJustifyRight()
{
    mEditor->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
}

void PQTextEditor::slotChangeFont(const QFont& font)
{
    QTextCharFormat format;
    format.setFont(font);
}

void PQTextEditor::slotChangeFontSize(int index)
{
    QFontDatabase db;
    int fontSize = db.standardSizes().at(index);

    QTextCharFormat format;
    format.setFontPointSize(fontSize);
}

void PQTextEditor::slotChangeColor()
{
     QColor col = QColorDialog::getColor(mEditor->textColor(), this);
     if (!col.isValid()) {
         return;
     }

     QTextCharFormat format;
     format.setForeground(col);
     mergeFormatOnWordOrSelection(format);
}


void PQTextEditor::slotChangeStyle(int index)
{
    QTextCursor cursor = mEditor->textCursor();

    if (index != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (index) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListCircle;
                break;
            case 3:
                style = QTextListFormat::ListSquare;
                break;
            case 4:
                style = QTextListFormat::ListDecimal;
                break;
            case 5:
                style = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                style = QTextListFormat::ListUpperAlpha;
                break;
            case 7:
                style = QTextListFormat::ListLowerRoman;
                break;
            case 8:
                style = QTextListFormat::ListUpperRoman;
                break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();
        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    } else {
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void PQTextEditor::mergeFormatOnWordOrSelection(const QTextCharFormat& format)
{
    QTextCursor cursor = mEditor->textCursor();
    if (!cursor.hasSelection()) {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    mEditor->mergeCurrentCharFormat(format);
}



#include "pqtexteditor.moc"
