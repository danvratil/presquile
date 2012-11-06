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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QHBoxLayout;

class PQComponentsPanel;
class PQComponentPropertiesPanel;
class PQComponentsAnimationsPanel;
class PQSlidesViewPanel;
class PQSlidePropertiesPanel;
class PQSlideDesigner;

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private Q_SLOTS:
    void slotNewPresentation();
    void slotOpenPresentation();
    void slotSavePresentation();
    void slotClosePresentation();
    void slotQuitPresquile();
    void slotHelp();
    void slotAboutPresquile();
    void slotAboutQt();

private:
    void setupActions();

    QHBoxLayout *mLayout;

    PQComponentsPanel *mComponentsPanel;
    PQComponentPropertiesPanel *mComponentPropertiesPanel;
    PQComponentsAnimationsPanel *mComponentsAnimationsPanel;
    PQSlidesViewPanel *mSlidesViewPanel;
    PQSlidePropertiesPanel *mSlidePropertiesPanel;
    PQSlideDesigner *mSlidesDesigner;

    QStatusBar *mStatusBar;

    QString mCurrentProject;

    int mChanged : 1;
};

#endif // MAINWINDOW_H
