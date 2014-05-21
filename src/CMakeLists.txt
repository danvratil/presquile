add_subdirectory(core)
add_subdirectory(declarative)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}/core
                    ${QT_INCLUDES}
)

set(presquile_SRCS
    animationselectdialog.cpp
    pqcomponentstreewidget.cpp
    pqslidesmodeldelegate.cpp
    pqslidedesigner.cpp
    main.cpp
    mainwindow.cpp

    editors/animationsequenceeditor.cpp
    editors/easingcurveeditor.cpp
    editors/propertieseditor.cpp
    editors/propertieseditoritem.cpp
    editors/propertyeditor.cpp
    editors/transformationseditor.cpp
    editors/pqtexteditor.cpp

    panels/pqcomponentpropertiespanel.cpp
    panels/pqcomponentsanimationspanel.cpp
    panels/pqslidesviewpanel.cpp
    panels/pqslidepropertiespanel.cpp
    panels/pqcomponentspanel.cpp
)

add_executable(presquile ${presquile_SRCS})

target_link_libraries(presquile
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}
    ${QT_QTDESIGNER_LIBRARY}
    PresquileCore
)

install(TARGETS presquile ${INSTALL_TARGETS_DEFAULT_ARGS})
