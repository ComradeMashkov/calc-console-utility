#pragma once

#include "data.hpp"

namespace calc_utility {

class Checker {
  public:
    explicit Checker(Result &result, int argc, char **argv)
        : result_(&result), argc_(argc), argv_(argv) {}

    void check() const;

  private:
    static bool check_argv(mathlib::IntMath &out, char **argv);

  private:
    int argc_;
    char **argv_;

    Result *result_;
};

} // namespace calc_utility
