/**
 * @file creditCalculation.h
 * @brief Заголовочный файл, описывающий библиотеки, использующиеся при
 * счёте кредитного калькулятора реалозованного на C
 */

#ifndef __CREDIT_CALCULATION__
#define __CREDIT_CALCULATION__
#include <math.h>

double creditAnnuitentCalc(double sumCredit, int monthTerm, double interestRate,
                           double *overpayment, double *totalPay);
double creditDifferentCalc(double sumCredit, int monthTerm, int *statePay,
                           double interestRate, double *overpayment,
                           double *totalPay);
#endif
