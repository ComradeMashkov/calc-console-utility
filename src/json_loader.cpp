#include "json_loader.hpp"
#include <fstream>

namespace calc_utility {

void JsonLoader::load() const {
    if (result_.state != State::JSON) {
        return;
    }

    if (result_.json_payload == nullptr) {
        throw std::runtime_error("Error: json payload is null.");
    }

    nlohmann::json j;
    try {
        j = nlohmann::json::parse(result_.json_payload);
    } catch (...) {
        throw std::runtime_error("Error: invalid json.");
    }

    if (!j.contains("opr") || !j["opr"].is_string()) {
        throw std::runtime_error("Error: json must contain string field \"opr\".");
    }

    const auto *opr_ptr = j["opr"].get_ptr<const nlohmann::json::string_t *>();
    if (opr_ptr == nullptr) {
        throw std::runtime_error("Error: cannot read \"op\" as string.");
    }
    const char *opr = opr_ptr->c_str();

    if (std::strcmp(opr, "add") == 0) {
        result_.state = State::ADD;
        result_.x.set(read_i64(j, "lhs"));
        result_.y.set(read_i64(j, "rhs"));
    } else if (std::strcmp(opr, "sub") == 0) {
        result_.state = State::SUB;
        result_.x.set(read_i64(j, "lhs"));
        result_.y.set(read_i64(j, "rhs"));
    } else if (std::strcmp(opr, "mul") == 0) {
        result_.state = State::MUL;
        result_.x.set(read_i64(j, "lhs"));
        result_.y.set(read_i64(j, "rhs"));
    } else if (std::strcmp(opr, "div") == 0) {
        result_.state = State::DIV;
        result_.x.set(read_i64(j, "lhs"));
        result_.y.set(read_i64(j, "rhs"));
    } else if (std::strcmp(opr, "pow") == 0) {
        result_.state = State::POW;
        result_.x.set(read_i64(j, "lhs"));
        result_.y.set(read_i64(j, "rhs"));
    } else if (std::strcmp(opr, "fac") == 0) {
        result_.state = State::FAC;
        result_.x.set(read_i64(j, "lhs"));
    } else {
        throw std::runtime_error("Error: unknown opr in json.");
    }
}

std::int64_t JsonLoader::read_i64(const nlohmann::json &j, const char *key) {
    if (!j.contains(key)) {
        char buf[kErrorBufSize];
        std::snprintf(buf, sizeof(buf), "Error: json missing field \"%s\".", key);
        throw std::runtime_error(buf);
    }
    if (!j[key].is_number_integer()) {
        char buf[kErrorBufSize];
        std::snprintf(buf, sizeof(buf), "Error: field \"%s\" must be an integer.", key);
        throw std::runtime_error(buf);
    }
    try {
        return j[key].get<std::int64_t>();
    } catch (...) {
        char buf[kErrorBufSize];
        std::snprintf(buf, sizeof(buf), "Error: field \"%s\" is out of int64 range.", key);
        throw std::runtime_error(buf);
    }
}

} // namespace calc_utility
