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

#include "mainwindow.h"

#include "panels/pqcomponentspanel.h"
#include "panels/pqcomponentpropertiespanel.h"
#include "panels/pqcomponentsanimationspanel.h"
#include "panels/pqslidesviewpanel.h"
#include "panels/pqslidepropertiespanel.h"
#include "pqslidedesigner.h"

#include "editors/animationsequenceeditor.h"

#include <QStatusBar>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QFileDialog>
#include <QPointer>
#include <QToolBar>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , mChanged(false)
{
    setWindowTitle(tr("Presquile"));

    setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
    setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
    setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
    setDockNestingEnabled(true);

    mComponentsPanel = new PQComponentsPanel(this);
    mComponentsPanel->setObjectName(QLatin1String("ComponentsPanel"));
    addDockWidget(Qt::LeftDockWidgetArea, mComponentsPanel);

    mComponentPropertiesPanel = new PQComponentPropertiesPanel(this);
    mComponentPropertiesPanel->setObjectName(QLatin1String("ComponentPropertiesPanel"));
    addDockWidget(Qt::LeftDockWidgetArea, mComponentPropertiesPanel);

    mComponentsAnimationsPanel = new PQComponentsAnimationsPanel(this);
    mComponentsAnimationsPanel->setObjectName(QLatin1String("ComponentsAnimationsPanel"));
    addDockWidget(Qt::BottomDockWidgetArea, mComponentsAnimationsPanel);

    mSlidesViewPanel = new PQSlidesViewPanel(this);
    mSlidesViewPanel->setObjectName(QLatin1String("SlidesViewPanel"));
    addDockWidget(Qt::RightDockWidgetArea, mSlidesViewPanel);

    mSlidePropertiesPanel = new PQSlidePropertiesPanel(this);
    mSlidePropertiesPanel->setObjectName(QLatin1String("SlidePropertiesPanel"));
    addDockWidget(Qt::RightDockWidgetArea, mSlidePropertiesPanel);

    mSlidesDesigner = new PQSlideDesigner(this);
    setCentralWidget(mSlidesDesigner);
    connect(mSlidesDesigner, SIGNAL(focusedItemChanged(QObject*)),
	    mComponentPropertiesPanel, SLOT(setItem(QObject*)));

    mStatusBar = new QStatusBar(this);
    setStatusBar(mStatusBar);

    setupActions();

    QSettings settings(QLatin1String("Presquile"), QLatin1String("MainApplication"));
    restoreGeometry(settings.value(QLatin1String("MainWindow/geometry")).toByteArray());
    restoreState(settings.value(QLatin1String("MainWindow/windowState")).toByteArray());
}

MainWindow::~MainWindow()
{
    QSettings settings(QLatin1String("Presquile"), QLatin1String("MainApplication"));
    settings.setValue(QLatin1String("MainWindow/geometry"), saveGeometry());
    settings.setValue(QLatin1String("MainWindow/windowState"), saveState());
}

void MainWindow::setupActions()
{
    QMenu *menu;
    QAction *action;
    QToolBar *toolBar;

    toolBar = addToolBar(tr("Main toolbar"));
    toolBar->setObjectName(QLatin1String("MainToolBar"));

    menu = menuBar()->addMenu(tr("&File"));
    action = menu->addAction(tr("&New Presentation"), this, SLOT(slotNewPresentation()), QKeySequence(Qt::CTRL + Qt::Key_N));
    action->setIcon(QIcon::fromTheme(QLatin1String("document-new")));
    toolBar->addAction(action);
    action = menu->addAction(tr("&Open Presentation"), this, SLOT(slotOpenPresentation()), QKeySequence(Qt::CTRL + Qt::Key_O));
    action->setIcon(QIcon::fromTheme(QLatin1String("document-open")));
    toolBar->addAction(action);
    action = menu->addAction(tr("&Save Presentation"), this, SLOT(slotSavePresentation()), QKeySequence(Qt::CTRL + Qt::Key_S));
    action->setIcon(QIcon::fromTheme(QLatin1String("document-save")));
    toolBar->addAction(action);
    action = menu->addAction(tr("&Close Presentation"), this, SLOT(slotClosePresentation()), QKeySequence(Qt::CTRL + Qt::Key_W));
    action->setIcon(QIcon::fromTheme(QLatin1String("window-close")));
    menu->addSeparator();
    action = menu->addAction(tr("&Quit Presquile"), this, SLOT(slotQuitPresquile()), QKeySequence(Qt::CTRL + Qt::Key_Q));
    action->setIcon(QIcon::fromTheme(QLatin1String("application-exit")));

    toolBar = addToolBar(tr("Presentation Toolbar"));
    toolBar->setObjectName(QLatin1String("PresentationToolBar"));

    menu = menuBar()->addMenu(tr("&Presentation"));
    action = menu->addAction(tr("&Run Presentation"), this, SLOT(slotRunPresentation()), QKeySequence(Qt::Key_F5));
    toolBar->addAction(action);
    action = menu->addAction(tr("Run From &Current Slide"), this, SLOT(slotRunFromCurrentSlide()), QKeySequence(Qt::SHIFT + Qt::Key_F5));
    toolBar->addAction(action);
    menu->addSeparator();
    toolBar->addSeparator();
    action = menu->addAction(tr("&Add Slide"), this, SLOT(slotAddSlide()), QKeySequence(Qt::CTRL + Qt::Key_N));
    toolBar->addAction(action);
    action = menu->addAction(tr("&Delete Slide"), this, SLOT(slotDeleteSlide()), QKeySequence(Qt::CTRL + Qt::Key_D));
    toolBar->addAction(action);


    menu = menuBar()->addMenu(tr("&Help"));
    menu->addAction(tr("&Help"), this, SLOT(slotHelp()), QKeySequence(Qt::Key_F1));
    menu->addSeparator();
    menu->addAction(tr("&About Presquile"), this, SLOT(slotAboutPresquile()));
    menu->addAction(tr("About &Qt"), this, SLOT(slotAboutQt()));
}

void MainWindow::slotNewPresentation()
{

}

void MainWindow::slotOpenPresentation()
{
    if (!mCurrentProject.isEmpty()) {
      slotClosePresentation();
    }

    QPointer<QFileDialog> dlg(new QFileDialog(this, tr("Open Presentation")));
    dlg->setAcceptMode(QFileDialog::AcceptOpen);
    dlg->setFileMode(QFileDialog::ExistingFile);
    dlg->setFilter(tr("Presquile Presentation (*.pqp)"));

    mCurrentProject.clear();
    if (dlg->exec()) {
	QStringList files = dlg->selectedFiles();
	if (!files.isEmpty()) {
	    mCurrentProject = files.first();
	}
    }

    /* TODO: Open presentation */
}

void MainWindow::slotSavePresentation()
{
    /* TODO: Save presentation */
}

void MainWindow::slotClosePresentation()
{
    /* TODO: Close presentation */
}

void MainWindow::slotQuitPresquile()
{
    slotClosePresentation();

    close();
}

void MainWindow::slotHelp()
{
    /* TODO: Help */
}

void MainWindow::slotAboutPresquile()
{
    /* TODO: About Presquile */

    QMessageBox::about(this, tr("About Presquile"), tr("<h1>Presquile</h1><p>&copy; 2012 Dan Vratil &lt;<a href=\"mailto:dan@progdan.cz\">dan@progdan.cz</a>&gt;"));
}

void MainWindow::slotAboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::slotRunPresentation()
{
    /* TODO: Run Presentation */
}

void MainWindow::slotRunFromCurrentSlide()
{
    /* TODO: Run From Current Slide */
}

void MainWindow::slotAddSlide()
{
    /* TODO: Add Slide */
}

void MainWindow::slotDeleteSlide()
{
    /* TODO: Remove Slide */
}


#include "mainwindow.moc"