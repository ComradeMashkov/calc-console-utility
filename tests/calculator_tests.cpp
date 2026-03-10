#include "calculator.hpp"
#include <cmath>
#include <gtest/gtest.h>

namespace calc_utility
{

class CalculatorTest : public ::testing::Test {
protected:
    Result res;

    void SetUp() override {
        res.x = mathlib::IntMath();
        res.y = mathlib::IntMath();
        res.i64 = mathlib::IntMath();
        res.d = mathlib::DblMath();
    }
};

TEST_F(CalculatorTest, AddOpr) {
    res.state = State::ADD;
    res.x.set(42);
    res.y.set(67);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());

    EXPECT_EQ(res.status, 0);
    EXPECT_EQ(res.i64.value(), 42 + 67);
}

TEST_F(CalculatorTest, AddOverflowOpr) {
    res.state = State::ADD;
    res.x.set(INT64_MAX);
    res.y.set(42);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());
    EXPECT_NE(res.status, 0);
}

TEST_F(CalculatorTest, SubOpr) {
    res.state = State::SUB;
    res.x.set(42);
    res.y.set(67);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());

    EXPECT_EQ(res.status, 0);
    EXPECT_EQ(res.i64.value(), 42 - 67);
}

TEST_F(CalculatorTest, SubOverflowOpr) {
    res.state = State::SUB;
    res.x.set(-INT64_MAX);
    res.y.set(42);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());
    EXPECT_NE(res.status, 0);
}

TEST_F(CalculatorTest, MulOpr) {
    res.state = State::MUL;
    res.x.set(42);
    res.y.set(67);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());

    EXPECT_EQ(res.status, 0);
    EXPECT_EQ(res.i64.value(), 42 * 67);
}

TEST_F(CalculatorTest, MulOverflowOpr) {
    res.state = State::MUL;
    res.x.set(INT64_MAX);
    res.y.set(42);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());
    EXPECT_NE(res.status, 0);
}

TEST_F(CalculatorTest, DivOpr) {
    res.state = State::DIV;
    res.x.set(42);
    res.y.set(3);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());

    EXPECT_EQ(res.status, 0);
    EXPECT_EQ(res.d.value(), 42.0 / 3.0);
}

TEST_F(CalculatorTest, DivByZeroOpr) {
    res.state = State::DIV;
    res.x.set(42);
    res.y.set(0);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());
    EXPECT_NE(res.status, 0);
}

TEST_F(CalculatorTest, PowOpr) {
    res.state = State::POW;
    res.x.set(2);
    res.y.set(10);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());

    EXPECT_EQ(res.status, 0);
    EXPECT_EQ(res.d.value(), std::pow(2, 10));
}

TEST_F(CalculatorTest, PowDivByZeroOpr) {
    res.state = State::POW;
    res.x.set(0);
    res.y.set(-1);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());
    EXPECT_NE(res.status, 0);
}

TEST_F(CalculatorTest, PowOverflowOpr) {
    res.state = State::POW;
    res.x.set(1000);
    res.y.set(1000);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());
    EXPECT_NE(res.status, 0);
}

TEST_F(CalculatorTest, FacOpr) {
    res.state = State::FAC;
    res.x.set(5);

    Calculator c(res);
    
    ASSERT_NO_THROW(c.calculate());

    EXPECT_EQ(res.status, 0);
    EXPECT_EQ(res.i64.value(), 120);
}

TEST_F(CalculatorTest, FacOverflowOpr) {
    res.state = State::FAC;
    res.x.set(21);

    Calculator c(res);

    ASSERT_NO_THROW(c.calculate());
    EXPECT_NE(res.status, 0);
}

} // namespace calc_utility