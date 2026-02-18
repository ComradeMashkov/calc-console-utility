#pragma once

#include "calculator.hpp"
#include "checker.hpp"
#include "parser.hpp"
#include "printer.hpp"

namespace calc_utility {

class Runner {
  public:
    explicit Runner(Result &result, int argc, char **argv)
        : parser_(result, argc, argv), checker_(result, argc, argv), calculator_(result),
          printer_(result) {}

    void run() const;

  private:
    Parser parser_;
    Checker checker_;
    Calculator calculator_;
    Printer printer_;
};

} // namespace calc_utility
