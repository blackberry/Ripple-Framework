find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtSql QtNetwork QtWebKit REQUIRED)
include(${QT_USE_FILE})

SET(RIPPLELIBRARY_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

LIST(APPEND RIPPLELIBRARY_HEADERS
    stdafx.h
    ConfigData.h
    PortScanner.h
    RemoteDebugger.h
)

LIST(APPEND RIPPLELIBRARY_SOURCES
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

SET(RIPPLELIBRARY_MOC_HEADERS
    QtStageWebView.h
    StageViewMsgHandler.h
    RequestObject.h
    BuildServerManager.h
    ScrollHandler.h
    RemoteDebugger.h
)

QT4_WRAP_CPP(RIPPLELIBRARY_MOC_SRCS ${RIPPLELIBRARY_MOC_HEADERS})

LIST(APPEND RIPPLELIBRARY_SOURCES ${RIPPLELIBRARY_HEADERS})
LIST(APPEND RIPPLELIBRARY_SOURCES ${RIPPLELIBRARY_MOC_HEADERS})
LIST(APPEND RIPPLELIBRARY_SOURCES ${RIPPLELIBRARY_MOC_SRCS})

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${RIPPLELIBRARY_INCLUDE_DIRECTORIES})
include_directories(${QT_INCLUDE_DIR})

ADD_LIBRARY(RippleLibrary ${RIPPLELIBRARY_SOURCES})
TARGET_LINK_LIBRARIES(RippleLibrary ${QT_LIBRARIES} ${optionalLibs})

INSTALL(TARGETS RippleLibrary DESTINATION ${CMAKE_BINARY_DIR}/bin)

