include_directories(${QT_INCLUDES}
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_BINARY_DIR}/src/core
                    ${CMAKE_CURRENT_BINARY_DIR}
)

set(qml_animations_SRCS
    qml/animations/ColorAnimation.qml
    qml/animations/NumberAnimation.qml
    qml/animations/ParallelAnimation.qml
    qml/animations/PauseAnimation.qml
    qml/animations/PropertyAnimation.qml
    qml/animations/RotationAnimation.qml
    qml/animations/SpringAnimation.qml
)

set(qml_components_SRCS
    qml/components/PQAnimatedImage.qml
    qml/components/PQImage.qml
    qml/components/PQRectangle.qml
    qml/components/PQResizable.qml
    qml/components/PQText.qml
)

set(qml_skeleton_SRCS
    qml/skeleton/PQSlide.qml
    qml/skeleton/PQPresentation.qml
)

set(pqplugin_SRCS
    pqitemframe.cpp
    pqplugin.cpp
)

add_library(pqdeclarativeplugin MODULE ${pqplugin_SRCS})
target_link_libraries(pqdeclarativeplugin
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTDECLARATIVE_LIBRARY}
                      PresquileCore
)


install(TARGETS pqdeclarativeplugin
        LIBRARY
        DESTINATION ${PRESQUILE_IMPORTS_INSTALL_DIR}/Presquile
)
install(FILES qmldir
        DESTINATION ${PRESQUILE_IMPORTS_INSTALL_DIR}/Presquile/
)
install(FILES ${qml_animations_SRCS}
        DESTINATION ${PRESQUILE_IMPORTS_INSTALL_DIR}/Presquile/qml/animations/
)
install(FILES ${qml_components_SRCS}
        DESTINATION ${PRESQUILE_IMPORTS_INSTALL_DIR}/Presquile/qml/components/
)
install(FILES ${qml_internals_SRCS}
        DESTINATION ${PRESQUILE_IMPORTS_INSTALL_DIR}/Presquile/qml/internals/
)
install(FILES ${qml_skeleton_SRCS}
        DESTINATION ${PRESQUILE_IMPORTS_INSTALL_DIR}/Presquile/qml/skeleton/
)
