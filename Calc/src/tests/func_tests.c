/**
 * @file func_tests.с
 * @brief Тестирование основного калькулятора, кредитного калькулятора и
 * депозитного калькулятора
 */
#include "func_tests.h"

/////////////////
/*  MAIN CALC  */
/////////////////

START_TEST(Main_calc_test_1) {
  char input[] = "5+10+97+0*log(12)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  ck_assert_double_eq(res, 112.000000);
}
END_TEST

START_TEST(Main_calc_test_2) {
  char input[] = "2^(2^(3))";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  ck_assert_double_eq(res, 256.000000);
}
END_TEST

START_TEST(Main_calc_test_3) {
  char input[] = "cos(15)+sin(30)/(atan(2)*sqrt(9))";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (-1.0571582)) < 1e-7 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_4) {
  char input[] = "cos(3-1)/sin(5)*tan(1)^(1)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (0.6758722)) < 1e-7 ? OK : FAILURE;
  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_5) {
  char input[] = "16mod(2+2)-(-1)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  ck_assert_double_eq(res, 1.000000);
}
END_TEST

START_TEST(Main_calc_test_6) {
  char input[] =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (-30.0722)) < 1e-4 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_7) {
  char input[] = "cos(3-1)/sin(5)*tan(1)^(1)";  //? 0.675872
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (0.675872)) < 1e-6 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_8) {
  char input[] = "15+1+4/(1-1)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = isinf(res) != 0 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_9) {
  char input[] = "ln(10)-(-log(2))";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (2.6036151)) < 1e-4 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_10) {
  char input[] = "cos(6)+sin(9)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (1.3722888)) < 1e-6 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_11) {
  char *input = "1/0";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = isinf(res) != 0 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_12) {
  char *input = "(cos(()))";
  char X[] = "";

  int error = 0;

  calculation(input, X, &error);

  int test_res = error == 0 ? OK : FAILURE;

  ck_assert_int_eq(test_res, FAILURE);
}
END_TEST

START_TEST(Main_calc_test_13) {
  char *input = "(sin((cos(log()))))";
  char X[] = "";

  int error = 0;

  calculation(input, X, &error);

  int test_res = error == 0 ? OK : FAILURE;

  ck_assert_int_eq(test_res, FAILURE);
}
END_TEST

START_TEST(Main_calc_test_14) {
  char *input = "((()))";
  char X[] = "";

  int error = 0;

  calculation(input, X, &error);

  int test_res = error == 0 ? OK : FAILURE;

  ck_assert_int_eq(test_res, FAILURE);
}
END_TEST

START_TEST(Main_calc_test_15) {
  char *input = "";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(Main_calc_test_16) {
  char *input = "-1";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  ck_assert_int_eq(res, -1);
}
END_TEST

START_TEST(Main_calc_test_17) {
  char *input = "0/0";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = isnan(res) == 1 ? OK : FAILURE;

  ck_assert_int_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_18) {
  char *input = "0/1";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(Main_calc_test_19) {
  char *input = "(cos(()))";
  char X[] = "";

  int error = 0;

  calculation(input, X, &error);

  int test_res = error == 0 ? OK : FAILURE;

  ck_assert_double_eq(test_res, FAILURE);
}
END_TEST

START_TEST(Main_calc_test_20) {
  char *input = "sin(cos(tan(asin(0))))";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (0.841471)) < 1e-6 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_21) {
  char *input = "sin(cos(tan(asin(1/0))))";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = isnan(res) == 1 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_22) {
  char *input = "sqrt(sqrt(sqrt(8)))";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);
  int test_res = fabsl(res - (1.29684)) < 1e-6 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_23) {
  char *input = "log(acos(atan(ln(sqrt(sqrt(sqrt(sqrt(sqrt(1)))))))))";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (0.196120)) < 1e-6 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_24) {
  char *input = "asin(4)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = isnan(res) == 1 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_25) {
  char *input = "3^(3)^(3)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (7625597484987)) < 1e-6 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_26) {
  char *input = "4^(-2)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (0.0625000)) < 1e-6 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_27) {
  char *input = "4^0";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(Main_calc_test_28) {
  char *input = "4^(0-1)";
  char X[] = "";

  double res = 0;
  int error = 0;

  res = calculation(input, X, &error);

  int test_res = fabsl(res - (0.2500000)) < 1e-6 ? OK : FAILURE;

  ck_assert_double_eq(test_res, OK);
}
END_TEST

START_TEST(Main_calc_test_29) {
  char *input = "weeeeee";
  char X[] = "";

  int error = 0;

  calculation(input, X, &error);

  int test_res = error == 0 ? OK : FAILURE;

  ck_assert_double_eq(test_res, FAILURE);
}
END_TEST

START_TEST(Main_calc_test_30) {
  char *input = "kto_proch1tal_tot_molodec";
  char X[] = "";

  int error = 0;

  calculation(input, X, &error);

  int test_res = error == 0 ? OK : FAILURE;

  ck_assert_double_eq(test_res, FAILURE);
}
END_TEST

///////////////////////
/*  LOAN CALCULATOR  */
///////////////////////

START_TEST(Loan_calc_test_1) {
  double overpayment = 0;
  double totalPay = 0;

  double res =
      creditAnnuitentCalc(100000, 12, 0.05 / 12, &overpayment, &totalPay);

  int test_res = fabsl(res - (8560.75)) < 1e-2 ? 0 : 1;

  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(Loan_calc_test_2) {
  double overpayment = 0;
  double totalPay = 0;

  creditAnnuitentCalc(100000, 12, 0.05 / 12, &overpayment, &totalPay);

  int test_res = fabsl(overpayment - (2728.98)) < 1e-2 ? 0 : 1;

  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(Loan_calc_test_3) {
  double overpayment = 0;
  double totalPay = 0;

  creditAnnuitentCalc(100000, 12, 0.05 / 12, &overpayment, &totalPay);

  int test_res = fabsl(totalPay - (102728.98)) < 1e-2 ? 0 : 1;

  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(Loan_calc_test_4) {
  double overpayment = 0;
  double totalPay = 0;

  double res = creditAnnuitentCalc(100000, 12, 0, &overpayment, &totalPay);

  int test_res = fabsl(res - (8333.33)) < 1e-2 ? 0 : 1;

  ck_assert_int_eq(test_res, 0);
}
END_TEST

//
START_TEST(Loan_calc_test_5) {
  int monthTerm = 12;
  int statePay = monthTerm - 1;

  double overpayment = 0;
  double totalPay = 0;

  for (int i = monthTerm - 1; i >= 0; i--) {
    creditDifferentCalc(100000, monthTerm, &statePay, 0.05 / 12, &overpayment,
                        &totalPay);
  }

  int test_res = fabsl(totalPay - (102708.33)) < 1e-2 ? 0 : 1;

  ck_assert_double_eq(test_res, 0);
}
END_TEST

START_TEST(Loan_calc_test_6) {
  int monthTerm = 12;
  int statePay = monthTerm - 1;

  double overpayment = 0;
  double totalPay = 0;

  for (int i = monthTerm - 1; i >= 0; i--) {
    creditDifferentCalc(100000, monthTerm, &statePay, 0.05 / 12, &overpayment,
                        &totalPay);
  }

  int test_res = fabsl(overpayment - (102708.33)) < 1e-2 ? 0 : 1;

  ck_assert_double_eq(test_res, 0);
}
END_TEST

START_TEST(Loan_calc_test_7) {
  int monthTerm = 12;
  int statePay = monthTerm - 1;

  double overpayment = 0;
  double totalPay = 0;
  double res = 0;

  for (int i = monthTerm - 1; i >= 0; i--) {
    res = creditDifferentCalc(100000, monthTerm, &statePay, 0.05 / 12,
                              &overpayment, &totalPay);
  }

  int test_res = fabsl(res - (8750.0)) < 1e-2 ? 0 : 1;

  ck_assert_int_eq(test_res, 0);
}
END_TEST

//////////////////////////
/*  DEPOSIT CALCULATOR  */
//////////////////////////

START_TEST(Dep_calc_test_1) {
  double sumPercent = 0;
  double sumNalog = 0;

  double res = depositCalc(50000, 12, 0.05, 0.1, 1, 1, 0, 0, 0, 0, &sumPercent,
                           &sumNalog);
  int test_res = fabsl(res - (52302.29)) < 1e-2 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(Dep_calc_test_2) {
  double sumPercent = 0;
  double sumNalog = 0;

  depositCalc(50000, 12, 0.05, 0.1, 1, 1, 0, 0, 0, 0, &sumPercent, &sumNalog);
  int test_res = fabsl(sumNalog - (255.81)) < 1e-2 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(Dep_calc_test_3) {
  double sumPercent = 0;
  double sumNalog = 0;

  depositCalc(50000, 12, 0.05, 0.1, 1, 1, 0, 0, 0, 0, &sumPercent, &sumNalog);
  int test_res = fabsl(sumPercent - (2558.09)) < 1e-2 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(Dep_calc_test_4) {
  double sumPercent = 0;
  double sumNalog = 0;

  double res = depositCalc(50000, 12, 0.05, 0.1, 1, 0, 0, 0, 0, 0, &sumPercent,
                           &sumNalog);
  int test_res = fabsl(res - (52250)) < 1e-2 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

START_TEST(Dep_calc_test_5) {
  double sumPercent = 0;
  double sumNalog = 0;

  double res = depositCalc(50000, 12, 0.05, 0.1, 1, 1, 3, 5000, 0, 0,
                           &sumPercent, &sumNalog);
  int test_res = fabsl(res - (72720.46)) < 1e-2 ? 0 : 1;
  ck_assert_int_eq(test_res, 0);
}
END_TEST

/*  TEST SUITES */

Suite *Main_calc_suit(void) {
  Suite *suite = suite_create("Main calculator");
  TCase *tc_core = tcase_create("core_of_Main_calc");
  tcase_add_test(tc_core, Main_calc_test_1);
  tcase_add_test(tc_core, Main_calc_test_2);
  tcase_add_test(tc_core, Main_calc_test_3);
  tcase_add_test(tc_core, Main_calc_test_4);
  tcase_add_test(tc_core, Main_calc_test_5);
  tcase_add_test(tc_core, Main_calc_test_6);
  tcase_add_test(tc_core, Main_calc_test_7);
  tcase_add_test(tc_core, Main_calc_test_8);
  tcase_add_test(tc_core, Main_calc_test_9);
  tcase_add_test(tc_core, Main_calc_test_10);
  tcase_add_test(tc_core, Main_calc_test_11);
  tcase_add_test(tc_core, Main_calc_test_12);
  tcase_add_test(tc_core, Main_calc_test_13);
  tcase_add_test(tc_core, Main_calc_test_14);
  tcase_add_test(tc_core, Main_calc_test_15);
  tcase_add_test(tc_core, Main_calc_test_16);
  tcase_add_test(tc_core, Main_calc_test_17);
  tcase_add_test(tc_core, Main_calc_test_18);
  tcase_add_test(tc_core, Main_calc_test_19);
  tcase_add_test(tc_core, Main_calc_test_20);
  tcase_add_test(tc_core, Main_calc_test_21);
  tcase_add_test(tc_core, Main_calc_test_22);
  tcase_add_test(tc_core, Main_calc_test_23);
  tcase_add_test(tc_core, Main_calc_test_24);
  tcase_add_test(tc_core, Main_calc_test_25);
  tcase_add_test(tc_core, Main_calc_test_26);
  tcase_add_test(tc_core, Main_calc_test_27);
  tcase_add_test(tc_core, Main_calc_test_28);
  tcase_add_test(tc_core, Main_calc_test_29);
  tcase_add_test(tc_core, Main_calc_test_30);
  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *Loan_calc_suit(void) {
  Suite *suite = suite_create("Loan calculator");
  TCase *tc_core = tcase_create("core_of_Loan_calc");
  tcase_add_test(tc_core, Loan_calc_test_1);
  tcase_add_test(tc_core, Loan_calc_test_2);
  tcase_add_test(tc_core, Loan_calc_test_3);
  tcase_add_test(tc_core, Loan_calc_test_4);
  tcase_add_test(tc_core, Loan_calc_test_5);
  tcase_add_test(tc_core, Loan_calc_test_6);
  tcase_add_test(tc_core, Loan_calc_test_7);

  suite_add_tcase(suite, tc_core);

  return suite;
}

Suite *Deposit_calc_suit(void) {
  Suite *suite = suite_create("Deposit calculator");
  TCase *tc_core = tcase_create("core_of_Deposit_calc");
  tcase_add_test(tc_core, Dep_calc_test_1);
  tcase_add_test(tc_core, Dep_calc_test_2);
  tcase_add_test(tc_core, Dep_calc_test_3);
  tcase_add_test(tc_core, Dep_calc_test_4);
  tcase_add_test(tc_core, Dep_calc_test_5);

  suite_add_tcase(suite, tc_core);

  return suite;
}

/*  TESTS MAIN */

int main(void) {
  int failed_count = 0;

  printf("---------------------------------------\n");
  SRunner *suite_runner = srunner_create(Main_calc_suit());
  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  printf("---------------------------------------\n");
  suite_runner = srunner_create(Loan_calc_suit());
  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  printf("---------------------------------------\n");
  suite_runner = srunner_create(Deposit_calc_suit());
  srunner_run_all(suite_runner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
  printf("---------------------------------------\n");

  return failed_count == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
