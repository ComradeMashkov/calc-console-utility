#include "checker.hpp"
#include "getopt.h"
#include <stdexcept>

namespace calc_utility {

void Checker::check() const {
    if (result_.state == State::NUL) {
        throw std::runtime_error("Error: no operation specified. Use calculator --help.");
    }

    const int needed = (result_.state == State::FAC) ? 1 : 2;
    if ((argc_ - optind) < needed) {
        throw std::runtime_error(
            "Error: not enough arguments. Use calculator --help for command format.");
    }

    if (!check_argv(result_.x, &argv_[optind])) {
        throw std::runtime_error(
            "Cannot parse input numbers. Use calculator --help for command format.");
    }

    if (result_.state != State::FAC) {
        if (!check_argv(result_.y, &argv_[optind + 1])) {
            throw std::runtime_error(
                "Cannot parse input numbers. Use calculator --help for command format.");
        }
    }
}

bool Checker::check_argv(mathlib::IntMath &out, char **argv) {
    if (argv == nullptr || *argv == nullptr || **argv == '\0') {
        return false;
    }

    char *s = *argv;
    char *end = nullptr;

    errno = 0;
    const int base = 10;
    const std::int64_t val = strtoll(s, &end, base);

    if (end == s) {
        return false;
    }

    if (*end != '\0') {
        return false;
    }

    if (errno == ERANGE) {
        return false;
    }

    out.set(val);
    return true;
}

} // namespace calc_utility
