#include "printer.hpp"
#include "logger.hpp"
#include <cstdio>

namespace calc_utility {

void Printer::print() const {
    if (result_->state == State::ADD || result_->state == State::SUB ||
        result_->state == State::MUL || result_->state == State::FAC) {
        Logger::instance().info("Result: {}", result_->i64.value());
    } else if (result_->state == State::DIV || result_->state == State::POW) {
        Logger::instance().info("Result: {}", result_->d.value());
    }
}

} // namespace calc_utility
