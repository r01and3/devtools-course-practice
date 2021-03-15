// Copyright 2021 Pronkin Dmitry

#include <gtest/gtest.h>

#include <tuple>
#include "include/complex_number.h"

TEST(Pronkin_Dmitry_ComplexNumberTest, Can_Create_Pointer) {
    double re = 13.0;
    double im = 13.0;
    ComplexNumber* z = new ComplexNumber(re, im);

    ASSERT_EQ(z->getRe(), re);
    ASSERT_EQ(z->getIm(), im);
}

typedef testing::TestWithParam<std::tuple<double, double>>
        Pronkin_Dmitry_ComplexNumberTest_Parametrized_2;
TEST_P(Pronkin_Dmitry_ComplexNumberTest_Parametrized_2,
       Multiplication_Complex_Conjugate) {
    double re = std::get<0>(GetParam());
    double im = std::get<1>(GetParam());
    ComplexNumber z1(re, im);
    ComplexNumber z2(re, -im);

    ComplexNumber z = z1 * z2;
    ComplexNumber result(re * re + im * im, 0.0);

    ASSERT_EQ(z, result);
}

INSTANTIATE_TEST_CASE_P(/**/, Pronkin_Dmitry_ComplexNumberTest_Parametrized_2,
    testing::Combine(
  testing::Values(-5.0, 3.0, 2.0, -3.0),
  testing::Values(1.3, 7.5, 4.8, 8.0)
));

typedef testing::TestWithParam<std::tuple<double, double, double, double>>
        Pronkin_Dmitry_ComplexNumberTest_Parametrized_4;
TEST_P(Pronkin_Dmitry_ComplexNumberTest_Parametrized_4,
       Multiplication_After_Division_Give_Original) {
    double re1 = std::get<0>(GetParam());
    double im1 = std::get<1>(GetParam());
    double re2 = std::get<2>(GetParam());
    double im2 = std::get<3>(GetParam());
    ComplexNumber z1(re1, im1);
    ComplexNumber z2(re2, im2);

    ComplexNumber z = z1 / z2;
    ComplexNumber result = z * z2;

    ASSERT_DOUBLE_EQ(result.getRe(), z1.getRe());
    ASSERT_DOUBLE_EQ(result.getIm(), z1.getIm());
}

INSTANTIATE_TEST_CASE_P(/**/, Pronkin_Dmitry_ComplexNumberTest_Parametrized_4,
    testing::Combine(
  testing::Values(5.0, 3.0, 5.0, 3.0),
  testing::Values(1.0, 7.0, 4.0, 8.0),
  testing::Values(2.0, 6.0, 7.0, 1.0),
  testing::Values(3.0, 3.0, 3.0, 3.0)
));
