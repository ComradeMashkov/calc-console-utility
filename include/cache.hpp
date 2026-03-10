#pragma once

#include "data.hpp"
#include "pq_shell.hpp"
#include <string>
#include <unordered_map>

namespace calc_utility {

class Cache {
  public:
    bool exists(const std::string &key) const;
    const Result &get(const std::string &key) const;
    void put(const std::string &key, const Result &r);

    void warm_up(PqShell &db);
    void save_to_db(PqShell &db, const Result &result);

    static std::string make_key(const Result &result);
    static std::string state_to_db_operations(State state);

  private:
    std::unordered_map<std::string, Result> cache_;
};

} // namespace calc_utility
