#pragma once

#include "data.hpp"

namespace calc_utility {

class Printer {
  public:
    explicit Printer(Result &result) : result_(&result) {}

    void print() const;

  private:
    Result *result_;
};

} // namespace calc_utility
