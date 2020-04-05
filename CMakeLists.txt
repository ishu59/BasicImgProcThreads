cmake_minimum_required(VERSION 3.1)
project(ImageProc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

find_package(OpenCV 4.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

add_executable(ImageProc src/main.cpp src/MultipleImageWindow.cpp src/NNProcessor.cpp)
target_link_libraries(ImageProc ${OpenCV_LIBRARIES})

add_executable(nnp src/nndriver.cpp src/NNProcessor.cpp)
target_link_libraries(nnp ${OpenCV_LIBRARIES})

add_executable(que src/queDriver.cpp)
target_link_libraries(que ${OpenCV_LIBRARIES})
file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add_executable(temp src/temp2.cpp)
#target_link_libraries(temp ${OpenCV_LIBRARIES})

