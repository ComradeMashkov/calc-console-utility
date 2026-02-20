#include "runner.hpp"
#include <cstdio>
#include <stdexcept>

namespace calc_utility {

void Runner::run() const {
    Logger::instance().info("Utility started.");
    parser_.parse();
    if (result_.state == State::JSON) {
        json_loader_.load();
    } else {
        checker_.check();
    }
    calculator_.calculate();
    printer_.print();
}

} // namespace calc_utility
