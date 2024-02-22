cmake_minimum_required(VERSION 3.10)

project(xml_validator VERSION 1.0)

set(SOURCES
    xml_validator.c
    xml_validator.h
)

find_package(LibXml2 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR})



# add_executable(${PROJECT_NAME} ${SOURCES})

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LIBXML2_LIBRARIES}) 