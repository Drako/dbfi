PROJECT ( dbfi C )
CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )

SET ( DBFI_VERSION_MAJOR "3" )
SET ( DBFI_VERSION_MINOR "0" )

SET ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )

# optional feature... enables compiler
OPTION ( WITH_COMPILER "enables the embedded compiler. requires libtcc" OFF )
IF ( WITH_COMPILER )
    FIND_PACKAGE ( LibTCC REQUIRED )
ENDIF ()

# for version information
FIND_PACKAGE ( Git REQUIRED )
INCLUDE ( GetGitRevisionDescription )
GET_GIT_HEAD_REVISION ( GIT_REFSPEC GIT_HASH )

SET ( CMAKE_INCLUDE_CURRENT_DIR ON )

ADD_SUBDIRECTORY ( src )

