#include "pqplugin.h"

#include "pqbaseitem.h"
#include "pqitemframe.h"

#include <qdeclarative.h>

void PQPlugin::registerTypes(const char *uri)
{
  // @uri presquile
  qmlRegisterType<PQBaseItem>(uri, 1, 0, "PQBaseItem");
  qmlRegisterType<PQItemFrame>(uri, 1, 0, "PQItemFrame");
}

Q_EXPORT_PLUGIN2(pqplugin, PQPlugin)

#include "pqplugin.moc"
