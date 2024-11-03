#include <gtest/gtest.h>
#include "StringCalculator.h"

TEST(StringCalculatorAddTests, ExpectZeroForEmptyInput) {
    int expectedresult = 0;
    std::string input = "";
    StringCalculator objUnderTest;
    int result = objUnderTest.CalculateAdd(input);

    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectZeroForSingleZero) {
    int expectedresult = 0;
    std::string input = "0";
    StringCalculator objUnderTest;
    int result = objUnderTest.CalculateAdd(input);

    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumForTwoNumbers) {
    int expectedresult = 3;
    std::string input = "1,2";
    StringCalculator objUnderTest;
    int result = objUnderTest.CalculateAdd(input);

    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectExceptionForNegativeNumbers) {
    ASSERT_THROW({
        std::string input = "-1,2";
        StringCalculator objUnderTest;
       objUnderTest.CalculateAdd(input);
        }, std::runtime_error);
}

TEST(StringCalculatorAddTests, ExpectSumWithNewlineDelimiter) {
    int expectedresult = 6;
    std::string input = "1\n2,3";
     StringCalculator objUnderTest;
    int result =objUnderTest.CalculateAdd(input);

    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, IgnoreNumbersGreaterThan1000) {
    int expectedresult = 1;
    std::string input = "1,1001";
    StringCalculator objUnderTest;
    int result =objUnderTest.CalculateAdd(input);

    ASSERT_EQ(result, expectedresult);
}

TEST(StringCalculatorAddTests, ExpectSumWithCustomDelimiter) {
    int expectedresult = 3;
    std::string input = "//;\n1;2";
    StringCalculator objUnderTest;
    int result = objUnderTest.CalculateAdd(input);

    ASSERT_EQ(result, expectedresult);
}

// test case for input with a number just below and above 1000 :Boundary condition
TEST(StringCalculatorAddTests, NumbersGreaterThan1000IgnoredInSum) {
    int expectedresult1 = 1001;
    std::string input1 = "999,2";
    StringCalculator objUnderTest;
    int result1 = objUnderTest.CalculateAdd(input1);
    ASSERT_EQ(result1, expectedresult1);

    int expectedresult2 = 2;
    std::string input2 = "1001,2";
    int result2 = objUnderTest.CalculateAdd(input2);
    ASSERT_EQ(result2, expectedresult2);
}

//test case for input with non-numeric strings
TEST(StringCalculatorAddTests, NonNumericInputReturnsZero) {
    int expectedresult = 0;
    std::string input = "Hello, world!";
    StringCalculator objUnderTest;
    int result = objUnderTest.CalculateAdd(input);

    ASSERT_EQ(result, expectedresult);
}
