/** PQPlugin -- Exports C++ classes to QML engine
 *  Copyright (C) 2014 Jan Stanek <khardix@gmail.com>
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PQPLUGIN_H
#define PQPLUGIN_H

#include <QDeclarativeExtensionPlugin>

/** @brief Exports plugin classes to QML engine */
class PQPlugin : public QDeclarativeExtensionPlugin
{
  Q_OBJECT

  public:
    void registerTypes(const char *uri);
};

#endif
