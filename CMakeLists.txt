cmake_minimum_required(VERSION 3.15...3.22)

project(bmpraytracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB SOURCES "src/*.cpp"", src/*.h")
file(GLOB TESTS "test/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp )
add_executable(test_${PROJECT_NAME} ${SOURCES} ${TESTS} )
target_link_libraries(test_${PROJECT_NAME} gtest_main)

include(GoogleTest)
gtest_discover_tests(test_${PROJECT_NAME})