#include "runner.hpp"
#include <cstdio>
#include <stdexcept>

namespace calc_utility {

void Runner::run() const {
    try {
        parser_.parse();
        if (result_->state == State::JSON) {
            json_loader_.load();
        } else {
            checker_.check();
        }
        calculator_.calculate();
        printer_.print();
    } catch (const HelpRequest &e) {
        fprintf(stdout, "%s", e.what());
    } catch (const std::exception &e) {
        fprintf(stderr, "%s", e.what());
    } catch (...) {
        fprintf(stderr, "An internal error occurred.\n");
    }
}

} // namespace calc_utility
