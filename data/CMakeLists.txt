if (WIN32)
  set(DATADIR "data/")
elseif (APPLE)
  set(DATADIR "Resources/")
else()
  set(DATADIR "share/")
endif()

add_subdirectory(qml)