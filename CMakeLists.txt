cmake_minimum_required(VERSION 3.20)

project(calculator LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    mathcalc
    GIT_REPOSITORY https://github.com/ComradeMashkov/calc-math-library.git
    GIT_TAG oop_calc_math_lib
)
FetchContent_MakeAvailable(mathcalc)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(spdlog)

include(CTest)
if (BUILD_TESTING)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

add_library(calc_core
    src/calculator.cpp
    src/checker.cpp
    src/parser.cpp
    src/printer.cpp
    src/runner.cpp
    src/json_loader.cpp
    src/logger.cpp
)

target_include_directories(calc_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(calc_core PUBLIC mathcalc nlohmann_json::nlohmann_json spdlog::spdlog)

add_executable(calculator src/main.cpp)
target_link_libraries(calculator PRIVATE calc_core)

if (BUILD_TESTING)
  add_executable(tests tests/parser_tests.cpp tests/checker_tests.cpp tests/calculator_tests.cpp tests/json_loader_tests.cpp)
  target_link_libraries(tests PRIVATE calc_core GTest::gtest_main)
  add_test(NAME tests COMMAND tests)
endif()

# clang-tidy
find_program(CLANG_TIDY_EXE NAMES clang-tidy)
if(CLANG_TIDY_EXE)
    set_target_properties(calculator PROPERTIES CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
endif()

# clang-format
find_program(CLANG_FORMAT_EXE NAMES clang-format)
if(CLANG_FORMAT_EXE)
    file(GLOB_RECURSE CALC_FORMAT_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    )

    add_custom_target(calculator-format
        COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${CALC_FORMAT_FILES}
    )

    if(TARGET mathcalc-format)
        add_dependencies(calculator-format mathcalc-format)
    endif()
endif()

install(TARGETS calculator
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)