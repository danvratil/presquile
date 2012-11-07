set(QML_ANIMATIONS
    animations/ColorAnimation.qml
    animations/NumberAnimation.qml
    animations/ParallelAnimation.qml
    animations/PauseAnimation.qml
    animations/PropertyAnimation.qml
    animations/RotationAnimation.qml
    animations/SpringAnimation.qml
)


install(FILES ${QML_ANIMATIONS} DESTINATION ${DATADIR}"/qml/animations/")