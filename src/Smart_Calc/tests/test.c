#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s21_smart_calc.h"

START_TEST(test_1) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  double x = 0;
  double result = 0;
  s21_parse("1*3-(10+55)/2*(30-(50-25))+4^2*2/(4-3*(2-5))", ex_str, &status);
  result = s21_callculation(ex_str, &status, x);
  ck_assert_float_eq(result, -157.038462);
}
END_TEST

START_TEST(test_2) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  double x = 0;
  double result = 0;
  s21_parse("log(10)-(-10)-ln(10)", ex_str, &status);
  result = s21_callculation(ex_str, &status, x);
  ck_assert_float_eq(result, 8.697415);
}
END_TEST

START_TEST(test_3) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  double x = 0;
  double result = 0;
  s21_parse("sin(5)-(+20)", ex_str, &status);
  result = s21_callculation(ex_str, &status, x);
  ck_assert_float_eq(result, -20.958924);
}
END_TEST

START_TEST(test_4) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  double x = 0;
  double result = 0;
  s21_parse("sin(cos(tan(1)))*20+1", ex_str, &status);
  result = s21_callculation(ex_str, &status, x);
  ck_assert_float_eq(result, 1.267756);
}
END_TEST

START_TEST(test_5) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  s21_parse("2..", ex_str, &status);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_6) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  s21_parse("2+2++", ex_str, &status);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_7) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  double x = 0;
  s21_parse("2+", ex_str, &status);
  s21_callculation(ex_str, &status, x);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_8) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  s21_parse("sin2", ex_str, &status);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_9) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  s21_parse("(1))", ex_str, &status);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_10) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  double x = 0;
  double result = 0;
  s21_parse("acos(0.1)*20+1", ex_str, &status);
  result = s21_callculation(ex_str, &status, x);
  ck_assert_float_eq(result, 30.412578);
}
END_TEST

START_TEST(test_11) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  double x = 0;
  double result = 0;
  s21_parse("asin(atan(sqrt(0.1)))*20+1+10mod5.1", ex_str, &status);
  result = s21_callculation(ex_str, &status, x);
  ck_assert_float_eq(result, 12.125600);
}
END_TEST

START_TEST(test_12) {
  char ex_str[MAX_STR] = {0};
  memset(ex_str, ' ', MAX_STR);
  int status = 0;
  double x = 0;
  s21_parse("*2-2*2/2-2mod3-sin(2)*cos(2)/tan(4)+asin(5)", ex_str, &status);
  s21_callculation(ex_str, &status, x);
  ck_assert_int_eq(status, 1);
}

Suite *s21_smart_calc_tests_create() {
  {
    Suite *s21_smart_calc = suite_create("s21_smart_calc");
    TCase *s21_smart_calc_tests = tcase_create("S21_SMART_CALC");
    tcase_add_test(s21_smart_calc_tests, test_1);
    tcase_add_test(s21_smart_calc_tests, test_2);
    tcase_add_test(s21_smart_calc_tests, test_3);
    tcase_add_test(s21_smart_calc_tests, test_4);
    tcase_add_test(s21_smart_calc_tests, test_5);
    tcase_add_test(s21_smart_calc_tests, test_6);
    tcase_add_test(s21_smart_calc_tests, test_7);
    tcase_add_test(s21_smart_calc_tests, test_8);
    tcase_add_test(s21_smart_calc_tests, test_9);
    tcase_add_test(s21_smart_calc_tests, test_10);
    tcase_add_test(s21_smart_calc_tests, test_11);
    tcase_add_test(s21_smart_calc_tests, test_12);
    suite_add_tcase(s21_smart_calc, s21_smart_calc_tests);
    return s21_smart_calc;
  }
}

END_TEST
int main() {
  Suite *s21_smart_calc = s21_smart_calc_tests_create();
  SRunner *s21_smart_calc_runner = srunner_create(s21_smart_calc);
  int number_failed;
  srunner_run_all(s21_smart_calc_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_smart_calc_runner);
  srunner_free(s21_smart_calc_runner);

  return number_failed == 0 ? 0 : 1;
}
