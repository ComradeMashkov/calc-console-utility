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
        res.json_path = nullptr;

        res.x = mathlib::IntMath();
        res.y = mathlib::IntMath();
    }
};

TEST_F(JsonLoaderTest, DoesNothingWhenStateNotJson) {
    res.state = State::ADD;

    JsonLoader j(res);

    EXPECT_NO_THROW(j.load());
    EXPECT_EQ(res.state, State::ADD);
}

TEST_F(JsonLoaderTest, ThrowsWhenPathNull) {
    res.state = State::JSON;
    res.json_path = nullptr;

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsWhenFileCannotBeOpened) {
    res.state = State::JSON;
    res.json_path = "/tmp/this_file_should_not_exist.json";
    
    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsOnInvalidJson) {
    res.state = State::JSON;
    res.json_path = "../input/invalid_json.json";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsWhenOprMissing) {
    res.state = State::JSON;
    res.json_path = "../input/opr_missing.json";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsWhenOprNotString) {
    res.state = State::JSON;
    res.json_path = "../input/opr_not_string.json";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsOnUnknownOpr) {
    res.state = State::JSON;
    res.json_path ="../input/unknown_opr.json";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, LoadsAdd) {
    res.state = State::JSON;
    res.json_path = "../input/add.json";

    JsonLoader j(res);

    ASSERT_NO_THROW(j.load());

    EXPECT_EQ(res.state, State::ADD);
    EXPECT_EQ(res.x.value(), 10);
    EXPECT_EQ(res.y.value(), 20);
}

TEST_F(JsonLoaderTest, LoadsFac) {
    res.state = State::JSON;
    res.json_path = "../input/fac.json";

    JsonLoader j(res);

    ASSERT_NO_THROW(j.load());

    EXPECT_EQ(res.state, State::FAC);
    EXPECT_EQ(res.x.value(), 5);
}

TEST_F(JsonLoaderTest, ThrowsWhenMissingRequiredField) {
    res.state = State::JSON;
    res.json_path =  "../input/missing_required_field.json";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}

TEST_F(JsonLoaderTest, ThrowsWhenFieldNotInteger) {
    res.state = State::JSON;
    res.json_path = "../input/field_not_integer.json";

    JsonLoader j(res);

    EXPECT_THROW(j.load(), std::runtime_error);
}
    
} // namespace calc_utility
