find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtSql QtNetwork QtWebKit REQUIRED)
include(${QT_USE_FILE})

SET(STARBUCKLIBRARY_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}/IPC/"
    "${CMAKE_SOURCE_DIR}/LIBS/boost_1_46_1"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

LIST(APPEND STARBUCKLIBRARY_SOURCES
    ConfigData.cpp
    #RIMStageWebView.cpp
    QtStageWebView.cpp
    StageViewMsgHandler.cpp
    xhrmsghandler.cpp
    BlackBerryBus.cpp
    RequestObject.cpp
    stdafx.cpp
)

SET(STARBUCKLIBRARY_MOC_HEADERS
    #RIMStageWebView.h
    QtStageWebView.h
    StageViewMsgHandler.h
    xhrmsghandler.h
    BlackBerryBus.h
    RequestObject.h
)

QT4_WRAP_CPP(STARBUCKLIBRARY_MOC_SRCS ${STARBUCKLIBRARY_MOC_HEADERS})

LIST(APPEND STARBUCKLIBRARY_SOURCES ${STARBUCKLIBRARY_MOC_SRCS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${STARBUCKLIBRARY_INCLUDE_DIRECTORIES})
include_directories(${QT_INCLUDE_DIR})

set(STARBUCKLIBRARY_LIBRARIES 
   ${IPC_LIBRARY_NAME}
#   ${WebKit_LIBRARY_NAME}
)

ADD_LIBRARY(StarbuckLibrary ${STARBUCKLIBRARY_SOURCES})
TARGET_LINK_LIBRARIES(StarbuckLibrary ${STARBUCKLIBRARY_LIBRARIES} ${QT_LIBRARIES} ${optionalLibs})

INSTALL(TARGETS StarbuckLibrary DESTINATION ${CMAKE_BINARY_DIR}/bin)

