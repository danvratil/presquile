include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_CURRENT_BINARY_DIR}
                    ${QT_INCLUDES}
)

################################################################################

set(TEXTEDITORTEST_SRCS
  texteditortest.cpp
  ../src/editors/pqtexteditor.cpp
)

qt4_automoc(${TEXTEDITORTEST_SRCS})

add_executable(text-editor-test
  ${TEXTEDITORTEST_SRCS}
)

target_link_libraries(text-editor-test
                      PresquileCore
                      ${QT_QTCORE_LIBRARY}
                      ${QT_QTGUI_LIBRARY}
)

################################################################################
