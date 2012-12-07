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


#include <QtGui/QApplication>

#include "src/editors/pqtexteditor.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    app.setApplicationName(QLatin1String("Presquile"));
    app.setApplicationVersion(QLatin1String("0.1.0"));
    app.setOrganizationDomain("progdan.cz");
    app.setOrganizationName("Dan Vrátil");

    PQTextEditor window;
    window.show();

    return app.exec();
}
