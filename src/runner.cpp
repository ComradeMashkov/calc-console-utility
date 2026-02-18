#include "runner.hpp"
#include "logger.hpp"
#include <cstdio>
#include <stdexcept>

namespace calc_utility {

void Runner::run() const {
    try {
        Logger::instance().info("Utility started.");
        parser_.parse();
        if (result_->state == State::JSON) {
            json_loader_.load();
        } else {
            checker_.check();
        }
        calculator_.calculate();
        printer_.print();
    } catch (const HelpRequest &e) {
        Logger::instance().info("{}", e.what());
    } catch (const std::exception &e) {
        Logger::instance().error("{}", e.what());
    } catch (...) {
        Logger::instance().error("An internal error occurred.");
    }
}

} // namespace calc_utility
