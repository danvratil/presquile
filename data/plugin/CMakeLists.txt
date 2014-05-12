set(pqplugin_SRCS
  pqbaseitem.cpp

  pqplugin.cpp
)
set(pqplugin_HEADERS
  pqbaseitem.h

  pqplugin.h
)

qt4_wrap_cpp(pqplugin_MOC ${pqplugin_HEADERS})

add_library(pqplugin MODULE ${pqplugin_SRCS} ${pqplugin_MOC})

install(TARGETS pqplugin LIBRARY DESTINATION "${DATADIR}/plugin")
