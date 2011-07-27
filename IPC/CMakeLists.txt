find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtSql QtNetwork QtWebKit REQUIRED)
include(${QT_USE_FILE})

SET(IPC_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

LIST(APPEND IPC_SOURCES
    ipcbridge.cpp
    ipcbridgeworker.cpp
    message.cpp
    messagehandler.cpp
    messagequeue.cpp
    samplemessagehandler.cpp
    stdafx.cpp
)

set(IPC_MOC_HEADERS
   ipcbridge.h
   ipcbridgeworker.h
   messagehandler.h
   samplemessagehandler.h
   messagequeue.h
)

QT4_WRAP_CPP(IPC_MOC_SRCS ${IPC_MOC_HEADERS})

list(APPEND IPC_SOURCES ${IPC_MOC_SRCS})

include_directories(${IPC_INCLUDE_DIRECTORIES})
include_directories(${QT_INCLUDE_DIR})

set(IPC_LIBRARIES
)

ADD_LIBRARY(IPC ${IPC_SOURCES})
TARGET_LINK_LIBRARIES(IPC ${IPC_LIBRARIES} ${QT_LIBRARIES} ${optionalLibs})

INSTALL(TARGETS IPC DESTINATION ${CMAKE_BINARY_DIR}/bin)
