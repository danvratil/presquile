/** PQPresentation -- Main object of Presquile presentation
  * Copyright (C) 2014 Jan Stanek <khardix@gmail.com>
  * 
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  * 
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  * 
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */ 
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
