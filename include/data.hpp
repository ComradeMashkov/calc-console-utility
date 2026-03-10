#pragma once

#include "calc_math_lib.hpp"
#include <cstdint>

namespace calc_utility {

enum class State : std::uint8_t { NUL, ADD, SUB, MUL, DIV, POW, FAC, JSON };

enum class ErrorCode : std::uint8_t {
    OK = 0,
    DIV_BY_ZERO = 1,
    OVERFLOW = 2,
    NEGATIVE_FACTORIAL = 3,
    UNKNOWN_ERROR = 100
};

struct Result {
    mathlib::IntMath x;
    mathlib::IntMath y;

    State state = State::NUL;

    mathlib::IntMath i64;
    mathlib::DblMath d;

    int status = 0;
    std::string error_msg;

    const char *json_payload = nullptr;
};

struct HelpRequest : std::exception {
    const char *what() const noexcept override {
        return "Usage: calculator [--add | --sub | --mul | --div | --pow] A B\n"
               "Usage: calculator --fac A\n"
               "Usage: calculator --json file.json\n"
               "Warning: for negative numbers use '--', e.g. calculator --add -- -1 -5";
    }
};

} // namespace calc_utility
