set(presquile_SRCS
    main.cpp
    mainwindow.cpp)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

qt4_automoc(${presquile_SRCS})
add_executable(presquile ${presquile_SRCS})
target_link_libraries(presquile
    ${QT_QTCORE_LIBRARY}
    ${QT_QTGUI_LIBRARY})

install(TARGETS presquile RUNTIME DESTINATION bin)
