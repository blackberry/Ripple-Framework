find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtSql QtNetwork QtWebKit REQUIRED)
include(${QT_USE_FILE})

SET(STARBUCKLIBRARY_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

LIST(APPEND STARBUCKLIBRARY_HEADERS
    stdafx.h
    ConfigData.h
    PortScanner.h
    RemoteDebugger.h
)

LIST(APPEND STARBUCKLIBRARY_SOURCES
    stdafx.cpp
    ConfigData.cpp
    QtStageWebView.cpp
    StageViewMsgHandler.cpp
    stdafx.cpp
    RequestObject.cpp
    BuildServerManager.cpp
    PortScanner.cpp
    ScrollHandler.cpp
    RemoteDebugger.cpp
)

SET(STARBUCKLIBRARY_MOC_HEADERS
    QtStageWebView.h
    StageViewMsgHandler.h
    RequestObject.h
    BuildServerManager.h
    ScrollHandler.h
    RemoteDebugger.h
)

QT4_WRAP_CPP(STARBUCKLIBRARY_MOC_SRCS ${STARBUCKLIBRARY_MOC_HEADERS})

LIST(APPEND STARBUCKLIBRARY_SOURCES ${STARBUCKLIBRARY_HEADERS})
LIST(APPEND STARBUCKLIBRARY_SOURCES ${STARBUCKLIBRARY_MOC_HEADERS})
LIST(APPEND STARBUCKLIBRARY_SOURCES ${STARBUCKLIBRARY_MOC_SRCS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${STARBUCKLIBRARY_INCLUDE_DIRECTORIES})
include_directories(${QT_INCLUDE_DIR})

ADD_LIBRARY(StarbuckLibrary ${STARBUCKLIBRARY_SOURCES})
TARGET_LINK_LIBRARIES(StarbuckLibrary ${QT_LIBRARIES} ${optionalLibs})

INSTALL(TARGETS StarbuckLibrary DESTINATION ${CMAKE_BINARY_DIR}/bin)

