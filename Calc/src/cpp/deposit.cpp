#include "deposit.h"

#include <QWidget>

#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent) : QDialog(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
  setWindowFlags(
      Qt::Dialog |
      Qt::MSWindowsFixedSizeDialogHint);  // для ограничения расширения окна
  connect(ui->startCalculate, SIGNAL(clicked()), this,
          SLOT(on_pushButton_clicked()));
}

Deposit::~Deposit() { delete ui; }

void Deposit::on_pushButton_clicked() {
  resetInputData();  // Обновление входных данных

  if (ui->Capitalisahion->isChecked())  // Капитализация
    capital = 1;
  else
    capital = 0;

  ui->depositResult->setText(QString::number(
      depositCalc(sumDeposit, monthTerm, interestRate, nalogRate, period,
                  capital, freqTime, refill, withdrawalCount, withdrawal,
                  &sumPercent, &sumNalog),
      'f', 2));
  ui->accruedResult->setText(QString::number(sumPercent, 'f', 2));
  ui->sumTaxResult->setText(QString::number(sumNalog, 'f', 2));
}

void Deposit::resetInputData() {
  sumDeposit = ui->depositStart->value();
  monthTerm = ui->period->value();
  interestRate = ui->persentBet->value();
  nalogRate = ui->taxBet->value();

  interestRate = interestRate / 100;
  nalogRate = nalogRate / 100;

  if (ui->periodPayment->currentIndex() == 0) {  // переодичность выплат
    period = 1;
  } else if (ui->periodPayment->currentIndex() == 1) {
    period = 3;
  } else if (ui->periodPayment->currentIndex() == 2) {
    period = 12;
  }

  if (ui->refillTime->currentIndex() == 0) {  // переодичность пополнений
    freqTime = -1;
  } else if (ui->refillTime->currentIndex() == 1) {
    freqTime = 1;
  } else if (ui->refillTime->currentIndex() == 2) {
    freqTime = 3;
  } else if (ui->refillTime->currentIndex() == 3) {
    freqTime = 12;
  }

  refill = ui->refillCount->value();

  if (ui->cutTime->currentIndex() == 0) {  // переодичность снятий
    withdrawalCount = -1;
  } else if (ui->cutTime->currentIndex() == 1) {
    withdrawalCount = 1;
  } else if (ui->cutTime->currentIndex() == 2) {
    withdrawalCount = 3;
  } else if (ui->cutTime->currentIndex() == 3) {
    withdrawalCount = 12;
  }

  withdrawal = ui->cutCount->value();

  sumPercent = 0;
  sumNalog = 0;
}
