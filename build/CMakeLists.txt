CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT(ishadowsocks)

SET(SRC_LIST ../src/main.cpp)
# debug
SET (CMAKE_BUILD_TYPE "DEBUG")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
ADD_EXECUTABLE(getishadow ${SRC_LIST})
TARGET_LINK_LIBRARIES(getishadow curl)

#release
#SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
#SET(CMAKE_BUILD_TYPE release)
#ADD_EXECUTABLE(getishadow ${SRC_LIST})
#TARGET_LINK_LIBRARIES(getishadow curl)
#INSTALL(PROGRAMS getishadow DESTINATION /usr/bin/)
