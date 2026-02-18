#pragma once

#include "data.hpp"

namespace calc_utility {

class Parser {
  public:
    explicit Parser(Result &result, int argc, char **argv)
        : result_(&result), argc_(argc), argv_(argv) {}

    void parse() const;

  private:
    void set_state(State state) const;

  private:
    int argc_;
    char **argv_;

    Result *result_;
};

} // namespace calc_utility
