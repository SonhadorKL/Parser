cmake_minimum_required(VERSION 3.22)
project(Testing)

include(CTest)

include(${Testing_SOURCE_DIR}/cmake/CodeCoverage.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Testing_SOURCE_DIR}/bin)

find_package(GTest REQUIRED)

include_directories(Testing ${Testing_SOURCE_DIR}/include)

set(SOURCE ${Testing_SOURCE_DIR}/src/FiniteAutomation.cpp ${Testing_SOURCE_DIR}/src/RegularExpression.cpp)

add_executable(tests ${Testing_SOURCE_DIR}/test/RegexTests.cpp ${SOURCE})
add_executable(solver ${Testing_SOURCE_DIR}/main.cpp ${SOURCE})
target_link_libraries(Testing ${GTEST_LIBRARIES})

append_coverage_compiler_flags()

setup_target_for_coverage_lcov(
    NAME regex_coverage
    EXECUTABLE ${Testing_SOURCE_DIR}/bin/tests
)