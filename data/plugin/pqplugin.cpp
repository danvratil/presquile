#include "pqplugin.h"

#include "pqbaseitem.h"

#include <qdeclarative.h>

void PQPlugin::registerTypes(const char *uri)
{
  qmlRegisterType<PQBaseItem>(uri, 1, 0, "PQBaseItem");
  qmlRegisterType<PQBaseItem>("Presquile", 1, 0, "PQBaseItem");
}

Q_EXPORT_PLUGIN2(pqplugin, PQPlugin);
