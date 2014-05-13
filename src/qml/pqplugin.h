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
