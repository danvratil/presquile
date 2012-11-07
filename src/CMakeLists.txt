set(presquile_SRCS
    animationselectdialog.cpp
    coreutils.cpp
    pqcomponentpropertiespanel.cpp
    pqcomponentsanimationspanel.cpp
    pqslidedesigner.cpp
    pqslidesviewpanel.cpp
    pqslidepropertiespanel.cpp
    pqcomponentspanel.cpp
    propertieseditor.cpp
    main.cpp
    mainwindow.cpp

    editors/animationsequenceeditor.cpp
    editors/easingcurveeditor.cpp
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
