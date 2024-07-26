#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QDialog>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "../deposit/depositCalculation.h"

#ifdef __cplusplus
}
#endif  // __cplusplus

namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 private:
  Ui::Deposit *ui;
  int capital;
  double sumDeposit;
  int monthTerm;
  double interestRate;
  double nalogRate;
  int period;

  int freqTime;
  int refill;

  int cutCount;
  int cut;

  int withdrawalCount;
  int withdrawal;

  double sumPercent;
  double sumNalog;

 private slots:
  void on_pushButton_clicked();
  void resetInputData();
};

#endif  // DEPOSIT_H
