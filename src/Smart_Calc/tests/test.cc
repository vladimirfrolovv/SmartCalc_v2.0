#include "../Controller/controller.h"
#include <gtest/gtest.h>


TEST(controller, some_expression) {
    s21::Controller *controller = new s21::Controller;
    std::string res = controller->GetResultStr("1*3-(10+55)/2*(30-(50-25))+4^2*2/(4-3*(2-5))", "0");
    EXPECT_DOUBLE_EQ(std::stold(res),-157.038462);
}
TEST(controller, log) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("log(10)-(-10)-ln(10)", "0");
EXPECT_DOUBLE_EQ(std::stold(res),8.697415);
}
TEST(controller, sin) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("sin(5)-(+20)", "0");
EXPECT_DOUBLE_EQ(std::stold(res),-20.958924);
}
TEST(controller, some_func) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("sin(cos(tan(1)))*20+1", "0");
EXPECT_DOUBLE_EQ(std::stold(res),1.267756);
}
TEST(controller, error_double_point) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("2..", "0");
EXPECT_EQ(res,"ERROR");
}
TEST(controller, error_double_op) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("2++", "0");
EXPECT_EQ(res,"ERROR");
}
TEST(controller, error_to_many_number) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("2+", "0");
EXPECT_EQ(res,"ERROR");
}
TEST(controller, error_2_brack) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("(1))", "0");
EXPECT_EQ(res,"ERROR");
}
TEST(controller, error_sin_without_brack) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("sin2", "0");
EXPECT_EQ(res,"ERROR");
}
TEST(controller, acos) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("acos(0.1)*20+1", "0");
EXPECT_DOUBLE_EQ(std::stold(res),30.412578);
}
TEST(controller, some_func_1) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("asin(atan(sqrt(0.1)))*20+1+10mod5.1", "0");
EXPECT_DOUBLE_EQ(std::stold(res),12.125600);
}
TEST(controller, error_big_exp) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("*2-2*2/2-2mod3-sin(2)*cos(2)/tan(4)+asin(5)", "0");
EXPECT_EQ(res,"ERROR");
}

TEST(controller, expresion_with_e) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("sqrt(4)*2.2/16e-2", "0");
EXPECT_DOUBLE_EQ(std::stold(res),27.5);
}
TEST(controller, expresion_with_e_error) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("sqrt(4)*2.2/16e2", "0");
EXPECT_EQ(res,"ERROR");
}
TEST(controller, brackets) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("((2))*3-(4+2)/(5*3)", "0");
EXPECT_DOUBLE_EQ(std::stold(res),5.6);
}
TEST(controller, with_x) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("((2))*3-(4+2)/(5*3)/x", "2");
EXPECT_DOUBLE_EQ(std::stold(res),5.8);
}
TEST(controller, brackets_sin) {
s21::Controller *controller = new s21::Controller;
std::string res = controller->GetResultStr("(sin(2))*3-(4+2)/(5*3)/x", "2");
EXPECT_DOUBLE_EQ(std::stold(res),2.527892);
}