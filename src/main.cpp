#include "runner.hpp"

int main(int argc, char **argv) {
    try {
        calc_utility::Result result;
        const calc_utility::Runner runner(result, argc, argv);
        runner.run();
    } catch (const calc_utility::HelpRequest &e) {
        calc_utility::Logger::instance().info("{}", e.what());
    } catch (const std::exception &e) {
        calc_utility::Logger::instance().error("{}", e.what());
    } catch (...) {
        calc_utility::Logger::instance().error("An internal error occurred.");
    }

    return 0;
}