set(qml_animations_SRCS
    animations/ColorAnimation.qml
    animations/NumberAnimation.qml
    animations/ParallelAnimation.qml
    animations/PauseAnimation.qml
    animations/PropertyAnimation.qml
    animations/RotationAnimation.qml
    animations/SpringAnimation.qml
)

set(qml_components_SRCS
    components/PQAnimatedImage.qml
    components/PQImage.qml
    components/PQRectangle.qml
    components/PQResizable.qml
    components/PQText.qml
)

set(qml_internals_SRCS
    internals/Slide.qml
)

set(qml_skeleton_SRCS
    skeleton/PQSlide.qml
    skeleton/PQPresentation.qml
)

set(pqplugin_SRCS
    pqbaseitem.cpp
    pqitemframe.cpp
    pqplugin.cpp
    pqqmlmanager.cpp
)

add_library(pqdeclarativeplugin MODULE ${pqplugin_SRCS})


install(TARGETS pqdeclarativeplugin
        LIBRARY
        DESTINATION ${QT_IMPORTS_DIR}/Presquile)
install(FILES qmldir
        DESTINATION ${QT_IMPORTS_DIR}/Presquile/qmldir)
install(FILES ${qml_animations_SRCS}
        DESTINATION ${QT_IMPORTS_DIR}/Presquile/qml/animations/)
install(FILES ${qml_components_SRCS}
        DESTINATION ${QT_IMPORTS_DIR}/Presquile/qml/components/)
install(FILES ${qml_internals_SRCS}
        DESTINATION ${QT_IMPORTS_DIR}/Presquile/qml/internals/)
install(FILES ${qml_skeleton_SRCS}
        DESTINATION ${QT_IMPORTS_DIR}/Presquile/qml/skeleton/)
