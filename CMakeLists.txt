CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Starbuck)


# -----------------------------------------------------------------------------
# Determine the target processor
# -----------------------------------------------------------------------------
IF (CMAKE_SYSTEM_PROCESSOR MATCHES "(arm|xscale)")
    SET(WTF_CPU_ARM 1)
    add_definitions(-DWTF_CPU_ARM=1)
ELSEIF (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)")
    SET(WTF_CPU_X86_64 1)
    add_definitions(-DWTF_CPU_X86_64=1)
ELSEIF (CMAKE_SYSTEM_PROCESSOR MATCHES "(i[3-6]86|x86)")
    SET(WTF_CPU_X86 1)
    add_definitions(-DWTF_CPU_X86=1)
ELSE ()
    MESSAGE(FATAL_ERROR "Unknown CPU '${CMAKE_SYSTEM_PROCESSOR}'")
ENDIF ()

#don't link the boot datatime library
ADD_DEFINITIONS(-DBOOST_DATE_TIME_NO_LIB)

# -----------------------------------------------------------------------------
# Determine the operating system
# -----------------------------------------------------------------------------
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
    SET(WTF_OS_UNIX 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    SET(WTF_OS_WINDOWS 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "RVCT")
    # FIXME: Better way of determining Olympia
    SET(WTF_OS_OLYMPIA 1)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    SET(WTF_OS_MAC_OS_X 1)
    #SET(CMAKE_OSX_ARCHITECTURES x86_64)
ELSE ()
    MESSAGE(WARNING "Unknown OS '${CMAKE_SYSTEM_NAME}'")
ENDIF ()

# -----------------------------------------------------------------------------
# Default target names (can be overrriden in Options${PORT}.cmake file)
# -----------------------------------------------------------------------------
SET(WebKit_LIBRARY_NAME WebKit)
SET(IPC_LIBRARY_NAME IPC)
SET(STARBUCKLIBRARY_LIBRARY_NAME StarbuckLibrary)


# -----------------------------------------------------------------------------
# Default library types (can be overrriden in Options${PORT}.cmake file)
# -----------------------------------------------------------------------------
SET(IPC_LIBRARY_TYPE STATIC)
SET(STARBUCKLIBRARY_LIBRARY_TYPE STATIC)

# -----------------------------------------------------------------------------
# Port-specific options
# -----------------------------------------------------------------------------
#INCLUDE(OptionsCommon)

SET(CMAKE_SRC ${CMAKE_SOURCE_DIR})
#SET(CMAKE_SOURCE_DIR "${OLYMPIA_DIR}")
#INCLUDE(Options${PORT})
SET(CMAKE_SOURCE_DIR ${CMAKE_SRC})


# -----------------------------------------------------------------------------
# Add module directories
# -----------------------------------------------------------------------------
ADD_SUBDIRECTORY(IPC)
ADD_SUBDIRECTORY(StarbuckLibrary)
ADD_SUBDIRECTORY(Starbuck)
ADD_SUBDIRECTORY(TestFramework)

#ADD_DEPENDENCIES(${IPC_LIBRARY_NAME} ${WebKit_LIBRARY_NAME})

ADD_DEPENDENCIES(${STARBUCKLIBRARY_LIBRARY_NAME} 
    ${IPC_LIBRARY_NAME} 
#    ${WebKit_LIBRARY_NAME}
)

ADD_DEPENDENCIES(Starbuck
    ${STARBUCKLIBRARY_LIBRARY_NAME} 
    ${IPC_LIBRARY_NAME} 
#    ${WebKit_LIBRARY_NAME}
)

ADD_DEPENDENCIES(TestFramework
    ${STARBUCKLIBRARY_LIBRARY_NAME} 
    ${IPC_LIBRARY_NAME} 
#    ${WebKit_LIBRARY_NAME}
)

#install olympia output to target
#INSTALL(DIRECTORY ${OLYMPIA_DIR}/build/bin DESTINATION ${CMAKE_BINARY_DIR})   

#install windows necessary libraries
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/libxml2/bin/libxml2.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/jpeg/bin/jpeg62.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/png/bin/libpng12.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/pthread/lib/pthreadvc2.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/iconv/bin/iconv.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/zlib/bin/zlib1.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/sqlite3/lib/sqlite3.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/icu/bin/icuuc36.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/icu/bin/icudt36.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
#  INSTALL(FILES ${OLYMPIA_DIR}/../webkitsupport/windows/msvcr71.dll DESTINATION ${CMAKE_BINARY_DIR}/bin)
ENDIF()    
