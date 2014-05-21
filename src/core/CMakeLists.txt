include_directories(${CMAKE_CURRENT_BINARY_DIR}
                    ${QT_INCLUDES})

set(core_SRCS
    pqbaseitem.cpp
    pqslide.cpp
    pqslidesmodel.cpp
    pqqmlloader.cpp
    coreutils.cpp
)


add_library(PresquileCore SHARED ${core_SRCS})
target_link_libraries(PresquileCore
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTDECLARATIVE_LIBRARY}
)
generate_export_header(PresquileCore
                       EXPORT_MACRO_NAME PRESQUILECORE_EXPORT
                       EXPORT_FILE_NAME presquile-core-export.h
)

set_target_properties(PresquileCore PROPERTIES
    #VERSION ${PRESQUILE_VERSION_STRING}
    #SOVERSION ${PRESQUILE_SOVERSION}
    EXPORT_NAME PresquileCore
)

install(TARGETS PresquileCore
        EXPORT PresquileTargets ${INSTALL_TARGETS_DEFAULT_ARGS}
)
