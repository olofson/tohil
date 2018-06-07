# Locate Tohil library
#
# This module defines:
#  TOHIL_FOUND, true if Tohil was found
#  TOHIL_INCLUDE_DIR, where the C headers are found
#  TOHIL_LIBRARY, where the library is found
#
# Created by David Olofson

FIND_PATH(TOHIL_INCLUDE_DIR tohil.h
	PATH_SUFFIXES include
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local/include/Tohil
	/usr/include/Tohil
	/sw/include/Tohil
	/opt/local/include/Tohil
	/opt/csw/include/Tohil
	/opt/include/Tohil
)

FIND_LIBRARY(TOHIL_LIBRARY
	NAMES tohil
	PATH_SUFFIXES lib64 lib
	PATHS
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/sw
	/opt/local
	/opt/csw
	/opt
)

SET(TOHIL_FOUND "NO")
IF(TOHIL_LIBRARY AND TOHIL_INCLUDE_DIR)
	SET(TOHIL_FOUND "YES")
ENDIF(TOHIL_LIBRARY AND TOHIL_INCLUDE_DIR)
