#Cmake file for httpclient
#Author:       zhouzongcheng
#Created:     2022/04/13
#PROJECT(TestHttp)                                             #定义工程名称
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -pthread")
add_definitions(-fPIC)

add_subdirectory(data)
add_subdirectory(http)
add_subdirectory(json)

INCLUDE_DIRECTORIES(                          #相关头文件的目录
${PROJECT_SOURCE_DIR}/include
)

set(SRCS HttpClientUtils.cpp)
#aux_source_directory(./HttpClientUtils.cpp SRCS)

ADD_LIBRARY(httpClient SHARED ${SRCS})         #生成静态链接库libassociation.a

target_link_directories(httpClient PRIVATE 
${PROJECT_SOURCE_DIR}/lib 
${PROJECT_BINARY_DIR}/lib 
${PROJECT_SOURCE_DIR}/Dll 
)
target_link_libraries(httpClient PRIVATE 
data
json
http
curl
pthread
)

             
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/Dll)
#SET_TARGET_PROPERTIES(association PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
#(utility  PROPERTIES RUNTIME_OUTPUT_DIRECTORY> "${PROJECT_SOURCE_DIR}/lib")  #表示生成的执行文件所在路径
