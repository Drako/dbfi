PROJECT ( dbfi )
CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )

SET ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )

# optional feature... enables compiler
FIND_PACKAGE ( LibTCC )

# for version information
FIND_PACKAGE ( Git REQUIRED )
INCLUDE ( GetGitRevisionDescription )
GET_GIT_HEAD_REVISION ( GIT_REFSPEC GIT_HASH )

SET ( CMAKE_INCLUDE_CURRENT_DIR ON )

ADD_SUBDIRECTORY ( src )

