set(QML_ANIMATIONS
      ColorAnimation.qml
      NumberAnimation.qml
      ParallelAnimation.qml
      PauseAnimation.qml
      PropertyAnimation.qml
      RotationAnimation.qml
      SpringAnimation.qml
)

set(QML_COMPONENTS
      PQAnimatedImage.qml
      PQImage.qml
      PQRectangle.qml
      PQResizable.qml
      PQText.qml
)

set(QML_INTERNALS
      Slide.qml
)

install(FILES ${QML_ANIMATIONS} DESTINATION ${DATADIR}"/qml/animations/")
install(FILES ${QML_COMPONENTS} DESTINATION ${DATADIR}"/qml/components/")
install(FILES ${QML_INTERNALS} DESTINATION ${DATADIR}"/qml/internals/")