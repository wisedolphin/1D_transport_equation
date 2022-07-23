project(Zone) #project name

set(SOURCE_LIB Zone.cpp Zone.h) #SOURCE_LIB var defenition

add_library(Zone STATIC ${SOURCE_LIB}) #static lib creation
