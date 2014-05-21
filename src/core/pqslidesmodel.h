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

#ifndef PQSLIDESMODEL_H
#define PQSLIDESMODEL_H


#include "presquile-core-export.h"

#include <QStandardItemModel>

#include "pqslide.h"

class PRESQUILECORE_EXPORT PQSlidesModel: public  QStandardItemModel
{
    Q_OBJECT
  public:
    enum {
        PQSlideRole = Qt::UserRole + 1,
    };

    explicit PQSlidesModel(QObject* parent = 0);
    virtual ~PQSlidesModel();

    void appendSlide(const PQSlide::Ptr &slide);
    void removeSlide(const PQSlide::Ptr &slide);
    int slideIndex(const PQSlide::Ptr &slide);
    PQSlide::Ptr slideAt(int index);

};

#endif // PQSLIDESMODEL_H
