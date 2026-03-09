#include "cache.hpp"

namespace calc_utility {

bool Cache::exists(const std::string &key) const {
    return cache_.find(key) != cache_.end();
}

const Result &Cache::get(const std::string &key) const {
    return cache_.at(key);
}

void Cache::put(const std::string &key, const Result &r) {
    cache_[key] = r;
}

void Cache::warm_up(PqShell &db) {
    cache_.clear();

    auto res = db.exec(
        "SELECT operand1, operand2, operation, result_int, result_double, status, error_msg "
        "FROM operations");

    for (int i = 0; i < res.rows(); ++i) {
        Result r;

        r.x.set(std::stoll(res.value(i, 0)));

        const std::string op = res.value(i, 2);
        if (op == "add") {
            r.state = State::ADD;
            r.y.set(std::stoll(res.value(i, 1)));
        } else if (op == "sub") {
            r.state = State::SUB;
            r.y.set(std::stoll(res.value(i, 1)));
        } else if (op == "mul") {
            r.state = State::MUL;
            r.y.set(std::stoll(res.value(i, 1)));
        } else if (op == "div") {
            r.state = State::DIV;
            r.y.set(std::stoll(res.value(i, 1)));
        } else if (op == "pow") {
            r.state = State::POW;
            r.y.set(std::stoll(res.value(i, 1)));
        } else if (op == "fac") {
            r.state = State::FAC;
        }

        if (!res.is_null(i, 3)) {
            r.i64.set(std::stoll(res.value(i, 3)));
        }

        if (!res.is_null(i, 4)) {
            r.d.set(std::stod(res.value(i, 4)));
        }

        if (!res.is_null(i, 5)) {
            r.status = std::stoi(res.value(i, 5));
        }

        if (!res.is_null(i, 6)) {
            r.error_msg = res.value(i, 6);
        }

        const std::string key = make_key(r);
        if (!key.empty()) {
            cache_[key] = r;
        }
    }
}

void Cache::save_to_db(PqShell &db, const Result &result) {
    const std::string operand1 = std::to_string(result.x.value());
    const std::string operand2 = std::to_string(result.y.value());
    const std::string operation = state_to_db_operations(result.state);
    const std::string status = std::to_string(result.status);

    std::string result_int;
    std::string result_double;

    const char *values[7];
    values[0] = operand1.c_str();

    if (result.state == State::FAC) {
        values[1] = nullptr;
    } else {
        values[1] = operand2.c_str();
    }

    values[2] = operation.c_str();

    if (result.state == State::ADD || result.state == State::SUB || result.state == State::MUL ||
        result.state == State::FAC) {
        result_int = std::to_string(result.i64.value());
        values[3] = result.status == 0 ? result_int.c_str() : nullptr;
        values[4] = nullptr;
    } else {
        result_double = std::to_string(result.d.value());
        values[3] = nullptr;
        values[4] = result.status == 0 ? result_double.c_str() : nullptr;
    }

    values[5] = status.c_str();
    values[6] = result.error_msg.empty() ? nullptr : result.error_msg.c_str();

    db.exec_params("INSERT INTO operations "
                   "(operand1, operand2, operation, result_int, result_double, status, error_msg) "
                   "VALUES ($1, $2, $3, $4, $5, $6, $7)",
                   7, values);
}

std::string Cache::make_key(const Result &result) {
    const auto x = result.x.value();
    const auto y = result.y.value();

    switch (result.state) {
    case State::ADD: {
        const auto a = std::min(x, y);
        const auto b = std::max(x, y);
        return std::to_string(a) + "+" + std::to_string(b);
    }
    case State::MUL: {
        const auto a = std::min(x, y);
        const auto b = std::max(x, y);
        return std::to_string(a) + "*" + std::to_string(b);
    }
    case State::SUB:
        return std::to_string(x) + "-" + std::to_string(y);
    case State::DIV:
        return std::to_string(x) + "/" + std::to_string(y);
    case State::POW:
        return std::to_string(x) + "^" + std::to_string(y);
    case State::FAC:
        return std::to_string(x) + "!";
    default:
        return {};
    }
}

std::string Cache::state_to_db_operations(State state) {
    switch (state) {
    case State::ADD:
        return "add";
    case State::SUB:
        return "sub";
    case State::MUL:
        return "mul";
    case State::DIV:
        return "div";
    case State::POW:
        return "pow";
    case State::FAC:
        return "fac";
    default:
        return "";
    }
}

} // namespace calc_utility
