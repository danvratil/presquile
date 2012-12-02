set(presquile_SRCS
    animationselectdialog.cpp
    coreutils.cpp
    pqcomponentstreewidget.cpp
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

    qml/pqqmlmanager.cpp
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

qt4_automoc(${presquile_SRCS})

add_executable(presquile ${presquile_SRCS})

target_link_libraries(presquile
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}
    ${QT_QTDESIGNER_LIBRARY}
)


install(TARGETS presquile RUNTIME DESTINATION bin)
