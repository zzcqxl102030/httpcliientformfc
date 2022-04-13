#Cmake file for HttpClient
#Author:       zhouzongcheng
#Created:     2022/04/13

cmake_minimum_required(VERSION 3.10)
project(TestHttp)
#find_package(Threads)
set(CMAKE_C_STANDARD 11 )#C11
set(CMAKE_CXX_STANDARD 17)#C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -pthread")

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

file(GLOB_RECURSE INCLUDES "./*.h" )

add_subdirectory(ZhouHttpClient)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 
SET(CMAKE_CXX_FLAGS "-O3")


add_executable(testHttp main.cpp  ${SOURCES} ${INCLUDES})

target_link_directories(testHttp PRIVATE 
${PROJECT_SOURCE_DIR}/lib 
${PROJECT_BINARY_DIR}/lib 
${PROJECT_SOURCE_DIR}/Dll 
)

target_link_libraries(testHttp PRIVATE 
http
data
json
curl
httpClient
)
add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/testHttp)
