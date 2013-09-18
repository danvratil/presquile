if (WIN32)
  set(DATADIR "data/")
elseif (APPLE)
  set(DATADIR "Resources/")
else()
  set(DATADIR "share/presquile")
endif()

add_subdirectory(qml)
