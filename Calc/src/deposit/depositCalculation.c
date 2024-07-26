#include "depositCalculation.h"

/// @brief Функция depositCalc предназначена для расчета депозита
/// с учетом различных параметров. Вот описание каждого параметра:
/// @param sumDeposit Сумма депозита, которую клиент хочет внести.
/// @param monthTerm Срок депозита в месяцах.
/// @param interestRate Ставка процента по депозиту.
/// @param nalogRate Ставка налога на доход, которая будет применяться к
/// процентам, полученным от депозита.
/// @param period Период, в течение которого будет производиться расчет
/// (например, ежемесячный).
/// @param capital Флаг, указывающий на то, будет ли капитализация процентов (1
/// - да, 0 - нет).
/// @param refillCount Количество пополнений депозита.
/// @param refill Сумма каждого пополнения.
/// @param withdrawalCount Количество снятий средств с депозита.
/// @param withdrawal Сумма каждого снятия.
/// @param sumPercent Указатель на переменную, в которую будет записан общий
/// процент, начисленный за весь срок депозита.
/// @param sumNalog Указатель на переменную, в которую будет записан общий налог
/// на доход, уплаченный за весь срок депозита.
/// @return Сумма на вкладе к концу срока
double depositCalc(double sumDeposit, int monthTerm, double interestRate,
                   double nalogRate, int period, int capital, int refillCount,
                   int refill, int withdrawalCount, int withdrawal,
                   double *sumPercent, double *sumNalog) {
  double sumDepositEnd = 0;
  if (capital == 0) {
    *sumPercent = sumDeposit * interestRate * monthTerm / 12;
    *sumNalog = nalogRate * (*sumPercent);
    sumDepositEnd = sumDeposit + *sumPercent - *sumNalog;

  } else if (capital == 1) {
    sumDepositEnd = sumDeposit;

    double currentPercent = 0;

    for (int i = 0, periodCurrent = 0, refillCurrent = 0, withdrawalCurrent = 0;
         i <= monthTerm;
         i++, periodCurrent++, refillCurrent++, withdrawalCurrent++) {
      if (refillCurrent == refillCount) {  // наступило время пополнения
        sumDepositEnd += refill;
        refillCurrent = 0;
      }
      if (withdrawalCurrent == withdrawalCount) {  // наступило время снятия
        sumDepositEnd -= withdrawal;
        withdrawalCurrent = 0;
      }
      if (periodCurrent == period) {  // капитализация процентов
        if (period == 1) currentPercent = (sumDepositEnd * interestRate) / 12.0;
        if (period == 3) currentPercent = (sumDepositEnd * interestRate) / 4.0;
        if (period == 12) currentPercent = (sumDepositEnd * interestRate);

        sumDepositEnd += currentPercent;
        *sumPercent += currentPercent;
        periodCurrent = 0;
      }
    }

    *sumNalog = nalogRate * (*sumPercent);
    sumDepositEnd -= *sumNalog;
  }

  return sumDepositEnd;
}