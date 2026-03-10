#include "runner.hpp"
#include <cstdio>
#include <stdexcept>

namespace calc_utility {

void Runner::run() {
    Logger::instance().info("Utility started.");

    cache_.warm_up(db_);

    parser_.parse();
    if (result_.state == State::JSON) {
        json_loader_.load();
    } else {
        checker_.check();
    }

    const std::string key = Cache::make_key(result_);

    if (!key.empty() && cache_.exists(key)) {
        Logger::instance().info("Result loaded from cache.");
        result_ = cache_.get(key);
    } else {
        calculator_.calculate();

        if (!key.empty()) {
            cache_.put(key, result_);
            cache_.save_to_db(db_, result_);
        }
    }

    printer_.print();
}

} // namespace calc_utility
