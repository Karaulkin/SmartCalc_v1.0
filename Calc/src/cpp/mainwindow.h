#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineEdit>
#include <QMainWindow>

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "../SmartCalc/s21_SmartCalc_v1.0.h"

#ifdef __cplusplus
}
#endif  // __cplusplus

#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  int error = 0;

 private:
  Ui::MainWindow *ui;
  // Graph ptr;

 private slots:
  void errorFunction(int error);
  void digits_numbersOperators();
  void constants();
  void clear();
  void calc();  // Счёт калкулятора
  void on_pushButton_Equal_clicked();
  void on_pushedButton_Graph_clicked();
  void on_pushButton_CreditCalc_clicked();
  void on_pushButton_DeposCalc_clicked();
};

#endif  // MAINWINDOW_H
