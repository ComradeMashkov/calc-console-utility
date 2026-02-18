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

add_executable(calculator src/main.cpp src/calculator.cpp src/checker.cpp src/parser.cpp src/printer.cpp src/runner.cpp src/json_loader.cpp)
target_include_directories(calculator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(calculator PRIVATE mathcalc nlohmann_json::nlohmann_json spdlog::spdlog)

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