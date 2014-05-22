/*
 * Copyright (C) 2014  Daniel Vrátil <dan@progdan.cz>
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

#include "pqserializer.h"
#include "pqslidesmodel.h"
#include "pqbaseitem.h"

#include <QTextStream>
#include <QDeclarativeItem>
#include <QGraphicsItem>


bool PQSerializer::serialize(QTextStream& output, PQSlidesModel* slidesModel)
{
    output << "import QtQuick 1.0" << endl;
    output << "import Presquile 1.0" << endl;
    output << endl;

    output << "PQPresentation {" << endl; // start presentation

    // Open slides list - one indentation step
    output << indentStep() << "slides: [" << endl;

    // Iterate over slides - two indentation steps
    for (int i = 0; i < slidesModel->rowCount(); ++i) {
        const PQSlide::Ptr currentSlide = slidesModel->slideAt(i);
        // Each slide must be wrapped in Component to prevent instantiating it on presentation load
        output << indentStep().repeated(2) << "Component {" << endl;
        output << indentStep().repeated(3) << "PQSlide {" << endl;

        QDeclarativeItem *container = currentSlide->rootObject()->findChild<QDeclarativeItem*>(QLatin1String("slideRootFocusScope"));
        if (!container) {
            qWarning("Invalid slide - no children container!");
        }

        const QList<QGraphicsItem*> data = container->childItems();
        // Iterate over the slide contents - three indentation steps
        for (QList<QGraphicsItem*>::const_iterator iter(data.begin()); iter < data.end(); ++iter) {
            PQBaseItem *child = qgraphicsitem_cast<PQBaseItem*>(*iter);
            if (!child) {
                qWarning("Invalid children");
                continue;
            }

            child->serialize(output, 4);
        }

        output << indentStep().repeated(3) << "}" << endl;
        output << indentStep().repeated(2) << "}";
        if (i < slidesModel->rowCount() - 1) {
            output << ','; // separator
        }
        output << endl;
    }

    output << indentStep() << ']' << endl; // close slides list
    output << '}' << endl; // close presentation

    return true;
}
