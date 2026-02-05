cmake_minimum_required(VERSION 3.20)

project(calculator LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    mathcalc
    GIT_REPOSITORY https://github.com/ComradeMashkov/calc-math-library.git
    GIT_TAG main
)

FetchContent_MakeAvailable(mathcalc)

add_executable(calculator src/calc_console_utility.cpp)
target_link_libraries(calculator PRIVATE mathcalc)

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