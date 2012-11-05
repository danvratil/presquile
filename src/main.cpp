/*
 * Copyright (C) 2012 Dan Vrátil <dan@progdan.cz>
 *
 * This file is part of Presquile.
 *
 * Presquile is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * Presquile is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGui/QApplication>

#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName(QLatin1String("Presquile"));
    app.setApplicationVersion(QLatin1String("0.1.0"));
    app.setOrganizationDomain("cz.progdan");
    app.setOrganizationName("Dan Vrátil");

    MainWindow window;
    window.show();

    return app.exec();
}
