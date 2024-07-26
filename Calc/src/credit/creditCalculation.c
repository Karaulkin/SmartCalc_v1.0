#include "creditCalculation.h"

/// @brief Аннуитетный кредитный калькулятор — это инструмент,
/// который позволяет рассчитать ежемесячные платежи по кредиту,
/// учитывая начальную сумму кредита, срок кредита, процентную ставку и
/// возможные доплаты. Входные параметры, которые вы указали, используются
/// для расчета:
/// @param sumCredit это начальная сумма кредита, которую нужно вернуть.
/// @param monthTerm это срок кредита в месяцах.
/// @param interestRate это годовая процентная ставка, которая применяется к
/// кредиту.
/// @param overpayment это указатель на переменную, в которую будет записан
/// размер доплаты, если она предусмотрена.
/// @param totalPay это указатель на переменную, в которую будет записан
/// общий размер платежей по кредиту.
/// @return Ежемесячный платёж по текущему месяцу
double creditAnnuitentCalc(double sumCredit, int monthTerm, double interestRate,
                           double *overpayment, double *totalPay) {
  double monthPayment = 0;

  if (interestRate != 0) {
    monthPayment =
        sumCredit * ((interestRate * pow((1 + interestRate), monthTerm)) /
                     (pow((1 + interestRate), monthTerm) - 1));
  } else {
    monthPayment = sumCredit / monthTerm;
  }
  *overpayment = (monthTerm * monthPayment) - sumCredit;
  *totalPay = monthPayment * monthTerm;
  return monthPayment;
}

/// @brief Дифференцированный кредитный калькулятор — это инструмент, который
/// позволяет рассчитать платежи по кредиту, учитывая различные ставки процента
/// за разные месяцы. Это может быть полезно, например, при рассчете кредитов
/// с дифференцированной процентной ставкой, где ставка меняется в зависимости
/// от срока кредита.
/// @param sumCredit Общая сумма кредита
/// @param monthTerm Срок в месяцах
/// @param statePay Сколько осталось платежей (изначально равно сроку в месяцах)
/// @param interestRate Процентная ставка
/// @param overpayment Переплата по кредиту
/// @param totalPay Общая выплата
/// @return Ежемесячный платёж по текущему месяцу
double creditDifferentCalc(double sumCredit, int monthTerm, int *statePay,
                           double interestRate, double *overpayment,
                           double *totalPay) {
  double monthlyPayment = 0;

  double balanceOfDebt = sumCredit - (sumCredit / monthTerm * (*statePay));
  monthlyPayment = (sumCredit / monthTerm) + (balanceOfDebt * interestRate);

  *totalPay = *totalPay + monthlyPayment;
  *overpayment = *overpayment + monthlyPayment;
  (*statePay)--;

  return monthlyPayment;
}
