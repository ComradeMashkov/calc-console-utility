#include "calculator.hpp"

namespace calc_utility {

void Calculator::calculate() const {
    try {

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

        result_.status = static_cast<int>(ErrorCode::OK);
        result_.error_msg.clear();
    } catch (const std::runtime_error &e) {

        result_.error_msg = e.what();

        std::string msg = e.what();

        if (msg.find("division by zero") != std::string::npos)
            result_.status = static_cast<int>(ErrorCode::DIV_BY_ZERO);

        else if (msg.find("overflow") != std::string::npos)
            result_.status = static_cast<int>(ErrorCode::OVERFLOW);

        else if (msg.find("factorial") != std::string::npos)
            result_.status = static_cast<int>(ErrorCode::NEGATIVE_FACTORIAL);

        else
            result_.status = static_cast<int>(ErrorCode::UNKNOWN_ERROR);
    }
}

} // namespace calc_utility
