#include "credit.h"

#include <QWidget>
#include <iostream>

#include "ui_credit.h"

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  connect(ui->pushButton_result, SIGNAL(clicked()), this,
          SLOT(on_pushButton_result()));
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_result() {
  resetInputData();

  if (ui->radioButton_annuity->isChecked()) annuitentCalc();
  if (ui->radioButton_differentiat->isChecked()) differentCalc();
}

void Credit::resetInputData() {
  sumCredit = ui->spinBox_totalLoan->value();
  monthTerm = ui->spinBox_month->value();
  interestRate = ui->doubleSpinBox_percent->value();

  interestRate = interestRate / 12 / 100;

  overpayment = 0;
  totalPay = 0;
  statePay = 0;
  monthPayment = 0;
}

void Credit::annuitentCalc() {
  monthPayment = creditAnnuitentCalc(sumCredit, monthTerm, interestRate,
                                     &overpayment, &totalPay);

  // Задаём размеры таблице
  ui->tableWidget_montPayment->setRowCount(
      monthTerm);  // задаём параметры таблицы
  ui->tableWidget_montPayment->setColumnCount(1);
  ui->tableWidget_montPayment->setHorizontalHeaderLabels(QStringList()
                                                         << "Выплаты");

  for (int i = 0; i < monthTerm; i++) {
    QString mP = QString::number(monthPayment, 'f', 2);
    QTableWidgetItem *table = new QTableWidgetItem(mP);
    ui->tableWidget_montPayment->setItem(0, i, table);
  }

  ui->label_resMonth->setText(QString::number(monthPayment, 'f', 2));
  ui->label_overpay->setText(QString::number(overpayment, 'f', 2));
  ui->label_totalCost->setText(QString::number(totalPay, 'f', 2));
}

void Credit::differentCalc() {
  statePay = monthTerm - 1;

  ui->tableWidget_montPayment->setRowCount(
      monthTerm);  // задаём параметры таблицы
  ui->tableWidget_montPayment->setColumnCount(1);
  ui->tableWidget_montPayment->setHorizontalHeaderLabels(QStringList()
                                                         << "Выплаты");

  for (int i = monthTerm - 1; i >= 0; i--) {  // расчёт ежемесячных выплат
    monthPayment = creditDifferentCalc(sumCredit, monthTerm, &statePay,
                                       interestRate, &overpayment, &totalPay);

    QString mP = QString::number(monthPayment, 'f', 2);

    QTableWidgetItem *table = new QTableWidgetItem(mP);
    ui->tableWidget_montPayment->setItem(0, i, table);
  }

  if (monthTerm != 0) overpayment = overpayment - sumCredit;

  ui->label_resMonth->setText(QString::number(monthPayment, 'f', 2));
  ui->label_overpay->setText(QString::number(overpayment, 'f', 2));
  ui->label_totalCost->setText(QString::number(totalPay, 'f', 2));
}
