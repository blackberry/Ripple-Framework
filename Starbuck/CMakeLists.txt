find_package(Qt4 COMPONENTS QtCore QtGui QtXml QtSql QtNetwork QtWebKit REQUIRED)
include(${QT_USE_FILE})

SET(STARBUCK_INCLUDE_DIRECTORIES
    "${CMAKE_BINARY_DIR}"
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/IPC"
    "${CMAKE_SOURCE_DIR}/StarbuckLibrary"
    "${CMAKE_CURRENT_SOURCE_DIR}"
    )

LIST(APPEND STARBUCK_SOURCES
    main.cpp
    starbuck.cpp
    stdafx.cpp
    )

set(STARBUCK_MOC_HEADERS
    starbuck.h    
    )

QT4_WRAP_CPP(STARBUCK_MOC_SRCS ${STARBUCK_MOC_HEADERS})

list(APPEND STARBUCK_SOURCES ${STARBUCK_MOC_SRCS} )

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${STARBUCK_INCLUDE_DIRECTORIES})
include_directories(${QT_INCLUDE_DIR})

set(STARBUCK_LIBRARIES
    ${IPC_LIBRARY_NAME}
    ${STARBUCKLIBRARY_LIBRARY_NAME}
#    ${WebKit_LIBRARY_NAME}
    )

#ADD_DEFINITIONS(-DIPC)


IF (WTF_OS_MAC_OS_X)
    ADD_EXECUTABLE(Starbuck MACOSX_BUNDLE ${STARBUCK_SOURCES})
    SET(LIBS ${STARBUCK_LIBRARIES} )

    SET(DIRS ${QT_BINARY_DIR} ${CMAKE_BINARY_DIR}/bin)

    SET(APPS ${CMAKE_BINARY_DIR}/bin/Starbuck.app)

    
ELSE ()
    ADD_EXECUTABLE(Starbuck ${STARBUCK_SOURCES})
ENDIF()


TARGET_LINK_LIBRARIES(Starbuck ${STARBUCK_LIBRARIES} ${QT_LIBRARIES} ${optionalLibs})

INSTALL(TARGETS Starbuck DESTINATION ${CMAKE_BINARY_DIR}/bin)
#INSTALL(FILES ${VG_DIR}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}${VG_LIB_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}
#    DESTINATION ${CMAKE_BINARY_DIR}/bin)

IF (WTF_OS_MAC_OS_X)
    INSTALL(CODE "
        include(BundleUtilities)
            fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
                " COMPONENT Runtime)
ENDIF()
