#include "parser.hpp"
#include "getopt.h"
#include <stdexcept>

namespace calc_utility {

void Parser::parse() const {
    int opt = 0;
    static const struct option longopts[] = {
        {"json", required_argument, nullptr, 'j'}, {"help", no_argument, nullptr, 'h'},
        {"add", no_argument, nullptr, 'a'},        {"sub", no_argument, nullptr, 's'},
        {"mul", no_argument, nullptr, 'm'},        {"div", no_argument, nullptr, 'd'},
        {"pow", no_argument, nullptr, 'p'},        {"fac", no_argument, nullptr, 'f'},
        {nullptr, no_argument, nullptr, '\0'}};

    int longind = 0;
    while ((opt = getopt_long(argc_, argv_, ":hasmdpfj:", longopts, &longind)) != -1) {
        switch (opt) {
        case 'j':
            if (result_.state != State::NUL) {
                throw std::runtime_error("Error: cannot combine --json with other operations.");
            }
            if (optarg == nullptr || *optarg == '\0') {
                throw std::runtime_error("Error: --json requires a file path.");
            }
            result_.state = State::JSON;
            result_.json_payload = optarg;
            break;
        case 'h':
            throw HelpRequest{};
            break;
        case 'a':
            set_state(State::ADD);
            break;
        case 's':
            set_state(State::SUB);
            break;
        case 'm':
            set_state(State::MUL);
            break;
        case 'd':
            set_state(State::DIV);
            break;
        case 'p':
            set_state(State::POW);
            break;
        case 'f':
            set_state(State::FAC);
            break;
        case ':':
            throw std::runtime_error("Error: option requires an argument.");
        case '?':
            throw std::runtime_error(
                "Unknown option. Use calculator --help for available commands.");
        default:
            throw std::runtime_error(
                "Error getting options. Use calculator --help for available commands.");
        }
    }
}

void Parser::set_state(State state) const {
    if (result_.state != State::NUL) {
        throw std::runtime_error(
            "Error: multiple operations specified. Choose exactly one. Use --help.");
    }

    result_.state = state;
}

} // namespace calc_utility
