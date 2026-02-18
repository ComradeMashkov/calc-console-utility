#pragma once

#include "calc_math_lib.hpp"
#include <cstdint>

namespace calc_utility {

enum class State : std::uint8_t { NUL, ADD, SUB, MUL, DIV, POW, FAC };

struct Result {
    mathlib::IntMath x;
    mathlib::IntMath y;

    State state = State::NUL;

    mathlib::IntMath i64;
    mathlib::DblMath d;
};

struct HelpRequest : std::exception {
    const char *what() const noexcept override {
        return "Usage: calculator [--add | --sub | --mul | --div | --pow] A B\n"
               "Usage: calculator --fac A\n"
               "Warning: for negative numbers use '--', e.g. calculator --add -- -1 -5\n";
    }
};

} // namespace calc_utility
