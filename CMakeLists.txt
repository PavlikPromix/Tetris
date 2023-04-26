cmake_minimum_required (VERSION 3.8)

project ("main")

find_package(SFML COMPONENTS system window graphics REQUIRED)

add_executable (main "main.cpp" "includes.h" "Piece.cpp" "Piece.h" "Grid.cpp" "Grid.h" "gui/Gui.cpp" "gui/Gui.h")

target_link_libraries(main PRIVATE sfml-system sfml-window sfml-graphics)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()
