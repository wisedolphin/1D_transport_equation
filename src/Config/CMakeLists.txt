project(Config) #project name

set(SOURCE_LIB Config.h) #SOURCE_LIB var defenition

add_library(Config STATIC ${SOURCE_LIB}) #static lib creation
