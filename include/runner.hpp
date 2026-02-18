#pragma once

#include "calculator.hpp"
#include "checker.hpp"
#include "json_loader.hpp"
#include "parser.hpp"
#include "printer.hpp"

namespace calc_utility {

class Runner {
  public:
    explicit Runner(Result &result, int argc, char **argv)
        : result_(&result), parser_(result, argc, argv), json_loader_(result),
          checker_(result, argc, argv), calculator_(result), printer_(result) {}

    void run() const;

  private:
    Result *result_;
    Parser parser_;
    JsonLoader json_loader_;
    Checker checker_;
    Calculator calculator_;
    Printer printer_;
};

} // namespace calc_utility
