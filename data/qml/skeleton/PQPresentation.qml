// Superobject of the presentation itself

import QtQuick 1.0

Item {
  property list<Component> slides
  property int slideIndex: 0

  anchors.margins: 50;
  focus: true
  
  Component {
    id: blackCurtain
    Rectangle {
      color: "black"
      anchors.fill: parent

      Text {
        id: endText
        color: 'white'

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 50

        text: "End of presentation"
      }
    }
  }

  Loader {
    id: slideLoader
    anchors.fill: parent
    sourceComponent: slides[0]
  }

  function loadNextSlide() {
    if (slideIndex < slides.length) {
      slideIndex += 1;
      slideLoader.sourceComponent = slides[slideIndex];
    }

    if (slideLoader.status == Loader.Null) { // end of slides
      slideLoader.sourceComponent = blackCurtain;
    }
  }
  function loadPrevSlide() {
    if (slideIndex >= 1) {
      slideIndex -= 1;
      slideLoader.sourceComponent = slides[slideIndex];
    }
  }

  MouseArea {
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton | Qt.RightButton
    onClicked: {
      if (mouse.button == Qt.RightButton) loadPrevSlide();
      else loadNextSlide();
    }
  }

  Keys.onSpacePressed: loadNextSlide();
  Keys.onRightPressed: loadNextSlide();
  Keys.onLeftPressed:  loadPrevSlide();
  Keys.onEscapePressed: Qt.quit();
}
