// Superobject of the presentation itself

import QtQuick 1.0

Item {
  property list<Component> slides
  property int nextSlideIndex: 0
  
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
    onLoaded: nextSlideIndex += 1
  }

  MouseArea {
    anchors.fill: parent
    onClicked: {
      slideLoader.sourceComponent = slides[nextSlideIndex];
      /* determine which status is set on non-existing slide
      if (slideLoader.status == Loader.Null) console.log('Null');
      else if (slideLoader.status == Loader.Ready) console.log('Ready');
      else if (slideLoader.status == Loader.Loading) console.log('Loading');
      else if (slideLoader.status == Loader.Error) console.log('Error');
      */
      if (slideLoader.status == Loader.Null) { // end of slides
        slideLoader.sourceComponent = blackCurtain;
      }
    }
  }
}
