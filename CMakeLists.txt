cmake_minimum_required(VERSION 3.2)
project(MoveNMergeIt)
find_package(Qt4 REQUIRED)

INCLUDE(${QT_USE_FILE})

# add definitions
ADD_DEFINITIONS(
  ${QT_DEFINITIONS} 
)

include_directories(
  src
  include
  images
)

set(HEADERS
  include/definitions.hpp
  include/position.hpp
  include/gui.hpp
  )

set(SOURCES
  src/position.cpp
  src/gui.cpp
  )

qt4_wrap_cpp(HEADERS_MOC ${HEADERS})

add_executable(movenmergeit
  src/main.cpp
  ${SOURCES}
  ${HEADERS_MOC}
  )

target_link_libraries(movenmergeit
  Qt4::QtGui
  Qt4::QtXml
  )

install(FILES
	images/blue.png
	images/green.png
	images/black.png
	images/pink.png
	images/orange.png
	images/red.png
	images/yellow.png
	images/white.png
	images/block.png
	DESTINATION ${PROJECT_BINARY_DIR}/images
)

