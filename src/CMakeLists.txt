# Author: Scott Marshall
# Date: 10 December 2014


if( UNIX )
# Sets the compilation flags to report all warnings and enable debugging in the generated
# object files and executable.
set( CMAKE_CXX_FLAGS "-Wall -g" )
ELSE( UNIX )
# Now we do for everyone else (e.g., Windows)
# Sets the compilation flags to report all meaningful warnings, and to ensure that
# we don't get silly warnings for exception handling semantics and unwinding
set( CMAKE_CXX_FLAGS "/W3 /EHsc" )
ENDIF(UNIX)


FILE(GLOB SRCS *.cpp *.h)

add_executable( weighs ${SRCS} )