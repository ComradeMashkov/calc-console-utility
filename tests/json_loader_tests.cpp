#include "checker.hpp"
#include "json_loader.hpp"
#include "parser.hpp"
#include <gtest/gtest.h>

namespace calc_utility
{

class JsonLoaderTest : public ::testing::Test {
protected:
    Result res;

    void SetUp() override {
        res.state = State::NUL;
        res.json_payload = nullptr;

        res.x = mathlib::IntMath();
        res.y = mathlib::IntMath();
    }
};

TEST_F(JsonLoaderTest, DoesNothingWhenStateNotJson) {
    res.state = State::ADD;
    res.json_payload = R"({"opr":"add","lhs":1,"rhs":2})";

    JsonLoader j(res);

    EXPECT_NO_THROW(j.load());
    EXPECT_EQ(res.state, State::ADD);
}

TEST_F(JsonLoaderTest, ThrowsWhenPayloadNull) {
    res.state = State::JSON;
    res.json_payload = nullptr;

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsOnInvalidJson) {
    res.state = State::JSON;
    res.json_payload = "{ not a json }";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsWhenOprMissing) {
    res.state = State::JSON;
    res.json_payload = R"({"lhs":10,"rhs":20})";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsWhenOprNotString) {
    res.state = State::JSON;
    res.json_payload = R"({"opr":123,"lhs":10,"rhs":20})";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsOnUnknownOpr) {
    res.state = State::JSON;
    res.json_payload = R"({"opr":"wat","lhs":10,"rhs":20})";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, LoadsAdd) {
    res.state = State::JSON;
    res.json_payload = R"({"opr":"add","lhs":10,"rhs":20})";

    JsonLoader j(res);

    ASSERT_NO_THROW(j.load());

    EXPECT_EQ(res.state, State::ADD);
    EXPECT_EQ(res.x.value(), 10);
    EXPECT_EQ(res.y.value(), 20);
}

TEST_F(JsonLoaderTest, LoadsFac) {
    res.state = State::JSON;
    res.json_payload = R"({"opr":"fac","lhs":5})";

    JsonLoader j(res);

    ASSERT_NO_THROW(j.load());

    EXPECT_EQ(res.state, State::FAC);
    EXPECT_EQ(res.x.value(), 5);
}

TEST_F(JsonLoaderTest, ThrowsWhenMissingRequiredField) {
    res.state = State::JSON;
    res.json_payload =  R"({"opr":"add","lhs":10})";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsWhenFieldNotInteger) {
    res.state = State::JSON;
    res.json_payload = R"({"opr":"add","lhs":10,"rhs":"20"})";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}
    
} // namespace calc_utility
