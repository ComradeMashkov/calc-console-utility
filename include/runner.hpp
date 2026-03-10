#pragma once

#include "cache.hpp"
#include "calculator.hpp"
#include "checker.hpp"
#include "json_loader.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "pq_shell.hpp"
#include "printer.hpp"

namespace calc_utility {

class Runner {
  public:
    explicit Runner(Result &result, int argc, char **argv)
        : result_(result), parser_(result, argc, argv), json_loader_(result),
          checker_(result, argc, argv), calculator_(result), printer_(result),
          db_("dbname=calculator_db user=postgres password=postgres host=localhost port=5432") {}

    void run();

  private:
    Parser parser_;
    JsonLoader json_loader_;
    Checker checker_;
    Calculator calculator_;
    Printer printer_;

    Result &result_;
    Cache cache_;
    PqShell db_;
};

} // namespace calc_utility
