#ifndef CREDIT_H
#define CREDIT_H

#include <QDialog>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "../credit/creditCalculation.h"

#ifdef __cplusplus
}
#endif  // __cplusplus

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private:
  Ui::Credit *ui;
  double sumCredit;
  int monthTerm;
  double interestRate;
  double overpayment;
  double totalPay;
  int statePay;
  double monthPayment;

 private slots:
  void on_pushButton_result();
  void resetInputData();
  void annuitentCalc();
  void differentCalc();
};

#endif  // CREDIT_H
