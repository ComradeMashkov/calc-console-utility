#include "runner.hpp"

int main(int argc, char **argv) {
    calc_utility::Result result;
    const calc_utility::Runner runner(result, argc, argv);
    runner.run();

    return 0;
}