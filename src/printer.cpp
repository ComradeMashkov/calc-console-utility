#include "printer.hpp"
#include <cstdio>

namespace calc_utility {

void Printer::print() const {
    if (result_->state == State::ADD || result_->state == State::SUB ||
        result_->state == State::MUL || result_->state == State::FAC) {
        fprintf(stdout, "Result: %lld\n", static_cast<long long>(result_->i64.value()));
    } else if (result_->state == State::DIV || result_->state == State::POW) {
        fprintf(stdout, "Result: %.4lf\n", result_->d.value());
    }
}

} // namespace calc_utility
