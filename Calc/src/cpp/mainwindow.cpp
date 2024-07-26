#include "mainwindow.h"

#include <QDebug>

#include "credit.h"
#include "deposit.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowFlags(
      Qt::Dialog |
      Qt::MSWindowsFixedSizeDialogHint);  // для ограничения расширения окна
  // NUMBERS
  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));
  // OPERATIONS
  connect(ui->pushButton_L, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // )
  connect(ui->pushButton_R, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // (
  connect(ui->pushButton_division, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // /
  connect(ui->pushButton_dot, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // .
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // -
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // mod
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // *
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // +
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // ^
  // FUNCTIONS
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // acos
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // asin
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // atan
  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // cos
  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // ln
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // log
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // sin
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // sqrt
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // tan
  connect(ui->pushButton_X, SIGNAL(clicked()), this,
          SLOT(digits_numbersOperators()));  // X !!!!!!1
  // CONST
  connect(ui->pushButton_Pi, SIGNAL(clicked()), this, SLOT(constants()));  // Pi
  connect(ui->pushButton_exp, SIGNAL(clicked()), this,
          SLOT(constants()));  // exp

  // RESULT
  connect(ui->pushButton_result, SIGNAL(clicked()), this,
          SLOT(on_pushButton_Equal_clicked()));  // =
  connect(ui->pushButton_delete, SIGNAL(clicked()), this,
          SLOT(clear()));  // delete
  // TOOLS
  connect(ui->pushButton_graph, SIGNAL(clicked()), this,
          SLOT(on_pushedButton_Graph_clicked()));  // graph
  connect(ui->pushButton_Credit, SIGNAL(clicked()), this,
          SLOT(on_pushButton_CreditCalc_clicked()));  // credit
  connect(ui->pushButton_Deposit, SIGNAL(clicked()), this,
          SLOT(on_pushButton_DeposCalc_clicked()));  // deposit
}
// Написать обычное добавление символов в string_show
// так как вычесление и проверки происходят на си

MainWindow::~MainWindow() { delete ui; }

void MainWindow::errorFunction(int error) {  // Вывод ошибки по коду
  switch (error) {
    case (-1):
      ui->result_show->setText("Некорректный символ!");
      break;
    case (1):
      ui->result_show->setText("Ошибка ввода sin/sqrt");
      break;
    case (2):
      ui->result_show->setText("Ошибка ввода cos");
      break;
    case (3):
      ui->result_show->setText("Ошибка ввода tan");
      break;
    case (4):
      ui->result_show->setText("Ошибка ввода asin/acos/atan");
      break;
    case (5):
      ui->result_show->setText("Ошибка ввода log/ln");
      break;
    case (6):
      ui->result_show->setText("Ошибка ввода mod");
      break;
    case (7):
      ui->result_show->setText("X не задан!");
      break;
    case (8):
      ui->result_show->setText("В дробном числе слишком много точек!");
      break;
    case (9):
      ui->result_show->setText("Два оператора не могут стоять рядом!");
      break;
    case (10):
      ui->result_show->setText("Пустые скобки не могут быть!");
      break;
    case (11):
      ui->result_show->setText("Ошибка в растановке знаков!");
      break;
    case (12):
      ui->result_show->setText("Число не может начинаться с точки!");
      break;
    case (13):
      ui->result_show->setText(
          "Перед открывающей скобкой должен быть оператор!");
      break;
    case (14):
      ui->result_show->setText(
          "Колличество открывающих и закрывающих скобок не тождественно!");
      break;
    case (15):
      ui->result_show->setText("Целое число не может начинаться с нуля!");
      break;
    case (16):
      ui->result_show->setText("Нет оператора между числом и функцией!");
      break;
    case (17):
      ui->result_show->setText("Ошибка в выражении!");
      break;
    case (18):
      ui->result_show->setText("Некорректно задан X!");
      break;
  }
}

void MainWindow::digits_numbersOperators() {
  if (error != 0) {  //если последняя операция ошибка стираем строку
    ui->result_show->setText("");
    error = 0;
  }
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  if ((button->text()).length() > 1 || button->text() == '^') {
    expression = ui->result_show->text() + button->text();

    expression = expression + "(";
  } else
    expression = ui->result_show->text() + button->text();

  ui->result_show->setText(expression);
}

void MainWindow::clear() {  // очистка дисплея
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  expression = ui->result_show->text();
  if (button->text() == "Delete") {
    expression.clear();
  }
  ui->result_show->setText(expression);
}

void MainWindow::constants() {  // обработка кнопок-констант
  if (error != 0) {  //если последняя операция ошибка стираем строку
    ui->result_show->setText("");
    error = 0;
  }
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  if (button->text() == "exp")
    expression = ui->result_show->text() + "e";
  else if (button->text() == "Pi")
    expression = ui->result_show->text() + "P";

  ui->result_show->setText(expression);
}

void MainWindow::calc() {  // функция вычисления
  error = 0;
  QString expression =
      QString::number(calculation(ui->result_show->text().toUtf8().data(),
                                  ui->value_X->text().toUtf8().data(), &error));
  if (error == 0) {
    ui->result_show->setText(expression);
  } else {
    errorFunction(error);  // проверить
  }
  if (expression == "nan" || expression == "inf")
    error = -2;  //код на nan и inf
}

void MainWindow::on_pushButton_Equal_clicked() {  // если нажали кнопку
                                                  // вычисления
  calc();
}

void MainWindow::on_pushedButton_Graph_clicked() {  // Построение графика
  Graph window;
  window.setModal(true);
  window.ui->label_text->setText(ui->result_show->text());
  window.exec();
}

void MainWindow::on_pushButton_CreditCalc_clicked() {  // Открыть окно кредитный
                                                       // калькулятор
  Credit window;
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_DeposCalc_clicked() {  // Открыть окно депозитный
                                                      // калькулятор
  Deposit window;
  window.setModal(true);
  window.exec();
}
