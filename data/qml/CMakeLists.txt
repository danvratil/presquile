set(QML_ANIMATIONS
      animations/ColorAnimation.qml
      animations/NumberAnimation.qml
      animations/ParallelAnimation.qml
      animations/PauseAnimation.qml
      animations/PropertyAnimation.qml
      animations/RotationAnimation.qml
      animations/SpringAnimation.qml
)

set(QML_COMPONENTS
      components/PQAnimatedImage.qml
      components/PQImage.qml
      components/PQRectangle.qml
      components/PQResizable.qml
      components/PQText.qml
)

set(QML_INTERNALS
      internals/Slide.qml
)

set(QML_SKELETON
      skeleton/PQSlide.qml
      skeleton/PQPresentation.qml
)

install(FILES ${QML_ANIMATIONS} DESTINATION "${MODULE_DIR}/qml/animations/")
install(FILES ${QML_COMPONENTS} DESTINATION "${MODULE_DIR}/qml/components/")
install(FILES ${QML_INTERNALS} DESTINATION "${MODULE_DIR}/qml/internals/")
install(FILES ${QML_SKELETON} DESTINATION "${MODULE_DIR}/qml/skeleton/")
