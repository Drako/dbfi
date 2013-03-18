CONFIGURE_FILE ( config.h.in config.h )

FILE ( GLOB dbfi_SOURCES *.c )
FILE ( GLOB dbfi_HEADERS *.h )

FILE ( GLOB dbfi_interpreter_SOURCES interpreter/*.c )
FILE ( GLOB dbfi_interpreter_HEADERS interpreter/*.h )

IF ( LIBTCC_FOUND )
    FILE ( GLOB dbfi_compiler_SOURCES compiler/*.c )
    FILE ( GLOB dbfi_compiler_HEADERS compiler/*.h )
    INCLUDE_DIRECTORIES ( ${LIBTCC_INCLUDE_DIRS} )
ENDIF ()

IF ( UNIX )
    SET ( UNIX_LIBRARIES dl )
ENDIF ()

ADD_EXECUTABLE (
    dbfi
    ${dbfi_SOURCES}             ${dbfi_HEADERS}
    ${dbfi_interpreter_SOURCES} ${dbfi_interpreter_HEADERS}
    ${dbfi_compiler_SOURCES}    ${dbfi_compiler_HEADERS}
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"
)
TARGET_LINK_LIBRARIES ( dbfi ${LIBTCC_LIBRARIES} ${UNIX_LIBRARIES} )
INSTALL ( TARGETS dbfi DESTINATION bin )
