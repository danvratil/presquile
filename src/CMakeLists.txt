set(pqplugin_HEADERS
  qml/pqplugin.h

  qml/pqbaseitem.h
  qml/pqqmlmanager.h
  qml/pqitemframe.h
)

foreach(header ${pqplugin_HEADERS})
  string(REPLACE ".h" ".cpp" src ${header})
  set(pqplugin_SRCS ${pqplugin_SRCS} ${src})
endforeach(header)

set(presquile_SRCS
    animationselectdialog.cpp
    coreutils.cpp
    pqcomponentstreewidget.cpp
    pqslide.cpp
    pqslidesmodel.cpp
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

    ${pqplugin_SRCS}
)

#set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#qt4_wrap_cpp(pqplugin_MOC ${pqplugin_HEADERS})
qt4_automoc(${pqplugin_SRCS})
qt4_automoc(${presquile_SRCS})

#add_library(pqplugin MODULE ${pqplugin_SRCS} ${pqplugin_MOC})
add_library(pqplugin MODULE ${pqplugin_SRCS})
add_executable(presquile ${presquile_SRCS})

target_link_libraries(presquile
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY}
    ${QT_QTDECLARATIVE_LIBRARY}
    ${QT_QTDESIGNER_LIBRARY}
)


install(TARGETS pqplugin presquile RUNTIME DESTINATION bin
                                   LIBRARY DESTINATION "${DATADIR}/plugin")
