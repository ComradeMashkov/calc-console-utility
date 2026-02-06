#include "calc_math_lib.hpp"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <getopt.h>

enum class State : std::uint8_t { NUL, ADD, SUB, MUL, DIV, POW, FAC, HLP, UNK, ERR, ARG, PRS, OPR };

struct Result {
    std::int64_t x = 0L;
    std::int64_t y = 0L;
    State state = State::NUL;
    double res = 0.0;
};

void check_argc(Result &result, State state, int argc, int argc_needed);
void parse(Result &result, int argc, char **argv);
bool check_argv(std::int64_t &out, char **argv);
void check(Result &result, char **argv);
void calculate(Result &result, mathlib::ErrorCode &ec);
void print(Result &result, mathlib::ErrorCode &ec);
void run(int argc, char **argv);

int main(int argc, char **argv) {
    run(argc, argv);

    return 0;
}

void check_argc(Result &result, State state, int argc, int argc_needed) {
    if ((argc - optind) < argc_needed) {
        result.state = State::ARG;
    } else {
        result.state = state;
    }
}

void parse(Result &result, int argc, char **argv) {
    int opt = 0;
    const struct option longopts[] = {
        {"help", no_argument, nullptr, 'h'}, {"add", no_argument, nullptr, 'a'},
        {"sub", no_argument, nullptr, 's'},  {"mul", no_argument, nullptr, 'm'},
        {"div", no_argument, nullptr, 'd'},  {"pow", no_argument, nullptr, 'p'},
        {"fac", no_argument, nullptr, 'f'},  {nullptr, no_argument, nullptr, '\0'}};

    int longind = 0;
    while ((opt = getopt_long(argc, argv, "hasmdpf", longopts, &longind)) != -1) {
        switch (opt) {
        case 'h':
            result.state = State::HLP;
            break;
        case 'a':
            check_argc(result, State::ADD, argc, 2);
            break;
        case 's':
            check_argc(result, State::SUB, argc, 2);
            break;
        case 'm':
            check_argc(result, State::MUL, argc, 2);
            break;
        case 'd':
            check_argc(result, State::DIV, argc, 2);
            break;
        case 'p':
            check_argc(result, State::POW, argc, 2);
            break;
        case 'f':
            check_argc(result, State::FAC, argc, 1);
            break;
        case '?':
            result.state = State::UNK;
            break;
        default:
            result.state = State::ERR;
            break;
        }
    }
}

bool check_argv(std::int64_t &out, char **argv) {
    if (argv == nullptr || *argv == nullptr || **argv == '\0') {
        return false;
    }

    char *s = *argv;
    char *end = nullptr;

    errno = 0;
    const int base = 10;
    const std::int64_t val = strtoll(s, &end, base);

    if (end == s) {
        return false;
    }

    if (*end != '\0') {
        return false;
    }

    if (errno == ERANGE) {
        return false;
    }

    out = static_cast<std::int64_t>(val);

    return true;
}

void check(Result &result, char **argv) {
    if ((result.state == State::HLP) || (result.state == State::ARG) ||
        (result.state == State::UNK) || (result.state == State::ERR)) {
        return;
    }

    if (!check_argv(result.x, &argv[optind])) {
        result.state = State::PRS;
        return;
    }

    if ((result.state != State::FAC) && (!check_argv(result.y, &argv[optind + 1]))) {
        result.state = State::PRS;
        return;
    }
}

void calculate(Result &result, mathlib::ErrorCode &ec) {
    switch (result.state) {
    case State::ADD:
        ec = mathlib::add(result.x, result.y, result.res);
        break;
    case State::SUB:
        ec = mathlib::sub(result.x, result.y, result.res);
        break;
    case State::MUL:
        ec = mathlib::mul(result.x, result.y, result.res);
        break;
    case State::DIV:
        ec = mathlib::div(result.x, result.y, result.res);
        break;
    case State::POW:
        ec = mathlib::pow(result.x, result.y, result.res);
        break;
    case State::FAC:
        ec = mathlib::fac(result.x, result.res);
        break;
    default:
        return;
    }

    if (ec != mathlib::ErrorCode::OK) {
        result.state = State::OPR;
    }
}

void print(Result &result, mathlib::ErrorCode &ec) {
    switch (result.state) {
    case State::HLP:
        fprintf(stdout, "Usage: calculator [--add | --sub | --mul | --div | --pow] A B\n");
        fprintf(stdout, "Usage: calculator --fac A\n");
        fprintf(stdout, "Warning: for negative numbers use '--', e.g. calculator --add -- -1 -5\n");
        break;
    case State::UNK:
        fprintf(stderr, "Unknown option. Use calculator --help for available commands.\n");
        break;
    case State::ERR:
        fprintf(stderr, "Error getting options. Use calculator --help for available comamnds.\n");
        break;
    case State::ARG:
        fprintf(stderr, "Error: not enough arguments. Use calculator --help for command format.\n");
        break;
    case State::PRS:
        fprintf(stderr, "Cannot parse input numbers. Use calculator --help for command format.\n");
        break;
    case State::OPR:
        fprintf(stderr, "Error executing operation: %s. Try something different.\n",
                mathlib::err_to_str(ec));
        break;
    case State::NUL:
        fprintf(stderr, "Error during program execution.\n");
        break;
    default:
        fprintf(stdout, "Result: %.4lf\n", result.res);
        break;
    }
}

void run(int argc, char **argv) {
    Result result{};
    mathlib::ErrorCode ec = mathlib::ErrorCode::NONE;

    parse(result, argc, argv);
    check(result, argv);
    calculate(result, ec);
    print(result, ec);
}
