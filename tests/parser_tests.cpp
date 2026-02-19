#include "parser.hpp"
#include <gtest/gtest.h>

namespace calc_utility
{

class ParserTest : public ::testing::Test {
protected:
    Result res;

    void SetUp() override {
        optind = 1;
        opterr = 0;

        res.state = State::NUL;
        res.json_path = nullptr;
    }
};

TEST_F(ParserTest, ParserAddFlag) {
    char prog[] = "calculator";
    char opt1[] = "--add";
    char* argv[] = { prog, opt1 };
    int argc = 2;
    
    Parser p(res, argc, argv);
    p.parse();

    EXPECT_EQ(res.state, State::ADD);
}

TEST_F(ParserTest, JsonSetsStateAndPath) {
    char prog[] = "calculator";
    char opt1[] = "--json";
    char opt2[] = "file.json";
    char* argv[] = { prog, opt1, opt2 };
    int argc = 3;

    Parser p(res, argc, argv);
    p.parse();

    EXPECT_EQ(res.state, State::JSON);
    EXPECT_STREQ(res.json_path, "file.json");
}

TEST_F(ParserTest, JsonCannotCombineWithOtherOps) {
    char prog[] = "calculator";
    char opt1[] = "--add";
    char opt2[] = "--json";
    char opt3[] = "file.json";
    char* argv[] = { prog, opt1, opt2, opt3 };
    int argc = 4;

    Parser p(res, argc, argv);

    EXPECT_THROW(p.parse(), std::runtime_error);
}

TEST_F(ParserTest, MultipleOpsRejected) {
    char prog[] = "calculator";
    char opt1[] = "--add";
    char opt2[] = "--sub";
    char* argv[] = { prog, opt1, opt2 };
    int argc = 3;

    Parser p(res, argc, argv);

    EXPECT_THROW(p.parse(), std::runtime_error);
}

TEST_F(ParserTest, HelpThrowsHelpRequest) {
    char prog[] = "calculator";
    char opt1[] = "--help";
    char* argv[] = { prog, opt1 };
    int argc = 2;

    Parser p(res, argc, argv);

    EXPECT_THROW(p.parse(), HelpRequest);
}

TEST_F(ParserTest, JsonRequiresArgument) {
    char prog[] = "calculator";
    char opt1[] = "--json";
    char* argv[] = { prog, opt1 };
    int argc = 2;

    Parser p(res, argc, argv);

    EXPECT_THROW(p.parse(), std::runtime_error);
}

TEST_F(ParserTest, UnknownOptionRejected) {
    char prog[] = "calculator";
    char opt1[] = "--unknown-option";
    char* argv[] = { prog, opt1 };
    int argc = 2;

    Parser p(res, argc, argv);

    EXPECT_THROW(p.parse(), std::runtime_error);
}
    
} // namespace calc_utility
