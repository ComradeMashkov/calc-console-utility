#include "calc_math_lib.hpp"
#include <cstdint>
#include <getopt.h>
#include <iostream>

int main(int argc, char **argv) {
    enum class OPCODE : std::uint8_t { NONE, ADD, SUB, MUL, DIV, POW, FAC };

    int opt = 0;
    const struct option longopts[] = {
        {"help", no_argument, nullptr, 'h'}, {"add", no_argument, nullptr, 'a'},
        {"sub", no_argument, nullptr, 's'},  {"mul", no_argument, nullptr, 'm'},
        {"div", no_argument, nullptr, 'd'},  {"pow", no_argument, nullptr, 'p'},
        {"fac", no_argument, nullptr, 'f'},  {nullptr, no_argument, nullptr, '\0'}};

    int longind = 0;
    OPCODE op = OPCODE::NONE;
    while ((opt = getopt_long(argc, argv, "hasmdpf", longopts, &longind)) != -1) {
        switch (opt) {
        case 'h':
            std::cout << "Usage: " << argv[0] << " [--add | --sub | --mul | --div | --pow] A B\n"
                      << "Usage: " << argv[0] << " --fac A\n"
                      << "Warning: for negative numbers use '--', e.g. " << argv[0]
                      << " --add -- -1 5\n";
            return 0;
        case 'a':
            op = OPCODE::ADD;
            break;
        case 's':
            op = OPCODE::SUB;
            break;
        case 'm':
            op = OPCODE::MUL;
            break;
        case 'd':
            op = OPCODE::DIV;
            break;
        case 'p':
            op = OPCODE::POW;
            break;
        case 'f':
            op = OPCODE::FAC;
            break;
        case '?':
            std::cerr << "Unknown option.\n";
            return 1;
        default:
            std::cerr << "Error parsing options.\n";
            return 1;
        }
    }

    const int needed = (op == OPCODE::FAC) ? 1 : 2;
    const int available = argc - optind;

    if (available < needed) {
        std::cerr << "Error: not enough arguments. Try " << argv[0] << " --help for help.\n";
        return 1;
    }

    const int a = atoi(argv[optind]);
    const int b = (op == OPCODE::FAC) ? 0 : atoi(argv[optind + 1]);

    double res = 0.0;

    try {
        switch (op) {
        case OPCODE::ADD:
            res = mathlib::add(a, b);
            break;
        case OPCODE::SUB:
            res = mathlib::sub(a, b);
            break;
        case OPCODE::MUL:
            res = mathlib::mul(a, b);
            break;
        case OPCODE::DIV:
            res = mathlib::div(a, b);
            break;
        case OPCODE::POW:
            res = mathlib::pow(a, b);
            break;
        case OPCODE::FAC:
            res = mathlib::fac(a);
            break;
        default:
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error while executing operation: " << e.what() << "\n";
        return 1;
    }

    std::cout << "Result: " << res << "\n";

    return 0;
}