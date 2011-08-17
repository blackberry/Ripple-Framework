find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtSql QtNetwork QtWebKit QtTest REQUIRED)
include(${QT_USE_FILE})

SET(TESTFRAMEWORK_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/StarbuckLibrary"
    "${CMAKE_CURRENT_SOURCE_DIR}"
  	"${CMAKE_CURRENT_SOURCE_DIR}/gmock-1.6.0"
	  "${CMAKE_CURRENT_SOURCE_DIR}/gmock-1.6.0/include"
	  "${CMAKE_CURRENT_SOURCE_DIR}/gmock-1.6.0/gtest"
	  "${CMAKE_CURRENT_SOURCE_DIR}/gmock-1.6.0/gtest/include"
)

LIST(APPEND TESTFRAMEWORK_SOURCES
	gmock-1.6.0/src/gmock-all.cc
	gmock-1.6.0/gtest/src/gtest-all.cc
	main.cpp
	MessageHandlerTest.cpp
	QtStageWebViewTest.cpp
)

set(TESTFRAMEWORK_MOC_HEADERS
	MessageSignalSpy.h
)

QT4_WRAP_CPP(TESTFRAMEWORK_MOC_SRCS ${TESTFRAMEWORK_MOC_HEADERS})

list(APPEND TESTFRAMEWORK_SOURCES ${TESTFRAMEWORK_MOC_SRCS} )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${TESTFRAMEWORK_INCLUDE_DIRECTORIES})
include_directories(${QT_INCLUDE_DIR})

set(TESTFRAMEWORK_LIBRARIES
    ${STARBUCKLIBRARY_LIBRARY_NAME}
)

ADD_EXECUTABLE(TestFramework ${TESTFRAMEWORK_SOURCES})
TARGET_LINK_LIBRARIES(TestFramework ${TESTFRAMEWORK_LIBRARIES} ${QT_LIBRARIES} ${optionalLibs})

INSTALL(TARGETS TestFramework DESTINATION ${CMAKE_BINARY_DIR}/bin)
