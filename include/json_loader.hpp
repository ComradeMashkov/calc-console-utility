#pragma once

#include "data.hpp"
#include <nlohmann/json.hpp>

namespace calc_utility {

class JsonLoader {
  public:
    explicit JsonLoader(Result &result) : result_(&result) {}

    void load() const;

  private:
    static std::int64_t read_i64(const nlohmann::json &j, const char *key);

  private:
    static constexpr std::size_t kErrorBufSize = 128;
    Result *result_;
};

} // namespace calc_utility
