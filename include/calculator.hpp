#pragma once

#include "data.hpp"

namespace calc_utility {

class Calculator {
  public:
    explicit Calculator(Result &result) : result_(result) {}

    void calculate() const;

  private:
    Result &result_;
};

} // namespace calc_utility
