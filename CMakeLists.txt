cmake_minimum_required (VERSION 3.12.4) # Set min. cmake version
project (main) # Name of project 

file (GLOB SOURCES_CPP "src/*.cpp")
file (GLOB HEADER_CPP "include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES_CPP}) # Compile file's
message("${CMAKE_CURRENT_SOURCE_DIR}/include)")
message("${PROJECT_SOURCE_DIR}/include)")

# Add my libs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add libcurl
FIND_PACKAGE(CURL REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ${CURL_LIBRARIES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIRS})

# Add nlohmann Json
FIND_PACKAGE(nlohmann_json REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

# Add curlpp
include_directories(${PROJECT_NAME} "/usr/include/curlpp")
target_link_libraries(${PROJECT_NAME} PUBLIC "/usr/lib64/libcurlpp.so")

# Add spdlog
include_directories(${PROJECT_NAME} "/usr/include/spdlog")
#target_link_libraries(${PROJECT_NAME} PUBLIC "/usr/lib64/libcurlpp.so"

# Set compile options
set_target_properties(PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

#set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*;-warnings-as-errors=*")
set_property(TARGET ${PROJECT_NAME}
    PROPERTY CXX_CLANG_TIDY clang-tidy;-checks=*;)
#    PROPERTY CXX_CLANG_TIDY clang-tidy;-checks=*;-warnings-as-errors=*)


if(nlohmann_json_FOUND)
  message("Find nlohmann json: [X]")
endif(nlohmann_json_FOUND)
if(CURL_FOUND)
  message("Find CURL: [X]")
endif(CURL_FOUND)
