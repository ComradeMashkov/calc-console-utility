#include "calculator.hpp"

namespace calc_utility {

void Calculator::calculate() const {
    switch (result_.state) {
    case State::ADD:
        result_.i64 = result_.x.add(result_.y);
        break;
    case State::SUB:
        result_.i64 = result_.x.sub(result_.y);
        break;
    case State::MUL:
        result_.i64 = result_.x.mul(result_.y);
        break;
    case State::DIV:
        result_.d = result_.x.div(result_.y);
        break;
    case State::POW:
        result_.d = result_.x.pow(result_.y);
        break;
    case State::FAC:
        result_.i64 = result_.x.fac();
        break;
    default:
        return;
    }
}

} // namespace calc_utility
