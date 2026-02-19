#include "checker.hpp"
#include "parser.hpp"
#include <gtest/gtest.h>

namespace calc_utility
{

class CheckerTest : public ::testing::Test {
protected:
    Result res;

    void SetUp() override {
        optind = 1;
        opterr = 0;

        res.state = State::NUL;
        res.x = mathlib::IntMath();
        res.y = mathlib::IntMath();
    }
};

TEST_F(CheckerTest, NoOperationSpecified) {
    char prog[] = "calculator";
    char* argv[] = { prog };
    int argc = 1;

    Checker c(res, argc, argv);

    EXPECT_THROW(c.check(), std::runtime_error);
}

TEST_F(CheckerTest, NotEnoughArgumentsForAdd) {
    char prog[] = "calculator";
    char opt1[] = "--add";
    char opt2[] = "5";
    char* argv[] = { prog, opt1, opt2 };
    int argc = 3;

    Parser p(res, argc, argv);
    p.parse();
    Checker c(res, argc, argv);

    EXPECT_THROW(c.check(), std::runtime_error);
}

TEST_F(CheckerTest, NotEnoughArgumentsForFac) {
    char prog[] = "calculator";
    char opt1[] = "--fac";
    char* argv[] = { prog, opt1 };
    int argc = 2;

    Parser p(res, argc, argv);
    p.parse();
    Checker c(res, argc, argv);

    EXPECT_THROW(c.check(), std::runtime_error);
}

TEST_F(CheckerTest, BadFirstArgChecking) {
    char prog[] = "calculator";
    char opt1[] = "--add";
    char opt2[] = "some_garbage";
    char opt3[] = "5";
    char* argv[] = { prog, opt1, opt2, opt3 };
    int argc = 4;

    Parser p(res, argc, argv);
    p.parse();
    Checker c(res, argc, argv);

    EXPECT_THROW(c.check(), std::runtime_error);
}

TEST_F(CheckerTest, BadSecondArgChecking) {
    char prog[] = "calculator";
    char opt1[] = "--add";
    char opt2[] = "5";
    char opt3[] = "some_garbage";
    char* argv[] = { prog, opt1, opt2, opt3 };
    int argc = 4;

    Parser p(res, argc, argv);
    p.parse();
    Checker c(res, argc, argv);

    EXPECT_THROW(c.check(), std::runtime_error);
}

TEST_F(CheckerTest, BadBothArgsChecking) {
    char prog[] = "calculator";
    char opt1[] = "--add";
    char opt2[] = "some_garbage";
    char opt3[] = "some_garbage";
    char* argv[] = { prog, opt1, opt2, opt3 };
    int argc = 4;

    Parser p(res, argc, argv);
    p.parse();
    Checker c(res, argc, argv);

    EXPECT_THROW(c.check(), std::runtime_error);
}

TEST_F(CheckerTest, ArgsChecking) {
    char prog[] = "calculator";
    char opt1[] = "--add";
    char opt2[] = "5";
    char opt3[] = "7";
    char* argv[] = { prog, opt1, opt2, opt3 };
    int argc = 4;

    Parser p(res, argc, argv);
    p.parse();
    Checker c(res, argc, argv);

    ASSERT_NO_THROW(c.check());

    EXPECT_EQ(res.x.value(), 5);
    EXPECT_EQ(res.y.value(), 7);
}

} // namespace calc_utility