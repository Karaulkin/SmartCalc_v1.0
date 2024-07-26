#include "s21_SmartCalc_v1.0.h"

/// @brief Процедура работы со стеком при осуществлении унарной операции:
/// вытаскиваем последнее число из стека чисел, проводим с ним унарную операцию,
/// удаляем операцию из стека операций, кладём результат в стек с числами
/// @param numbersStack стек с числами
/// @param symStack стек с операциями
void stackUnarOperation(stack **numbersStack, stack **symStack) {
  double lastNumber = 0;
  lastNumber = (*numbersStack)->number;
  popStack(numbersStack);
  lastNumber = unarOperation(lastNumber, (*symStack)->sym);
  popStack(symStack);
  pushStack(numbersStack, lastNumber, '\0');
}

/// @brief Процедура работы со стеком при осуществлении арифметической операции
/// с двумя аргументами: вытаскиваем последние два числа из стека чисел,
/// проводим с ними арифметическую операцию, удаляем операцию из стека операций,
/// кладём результат в стек с числами
/// @param numbersStack стек с числами
/// @param symStack стек с операциями
void stackDoubleOperation(stack **numbersStack, stack **symStack) {
  double lastNumber = 0, preLastNumber = 0;
  lastNumber = (*numbersStack)->number;
  popStack(numbersStack);
  preLastNumber = (*numbersStack)->number;
  popStack(numbersStack);
  lastNumber = doubleOperation(lastNumber, preLastNumber, (*symStack)->sym);
  popStack(symStack);
  pushStack(numbersStack, lastNumber, '\0');
}

/// @brief Вычисление арифметических операция с двумя аргументами
/// @param lastNumber второй аргумент
/// @param preLastNumber первый аргумент
/// @param operation вид арифметической операции
/// @return результат
double doubleOperation(double lastNumber, double preLastNumber,
                       char operation) {
  double result = 0;
  switch (operation) {
    case '+':
      result = preLastNumber + lastNumber;
      break;
    case '-':
      result = preLastNumber - lastNumber;
      break;
    case '*':
      result = preLastNumber * lastNumber;
      break;
    case '/':
      result = preLastNumber / lastNumber;
      break;
    case '^':
      result = pow(preLastNumber, lastNumber);
      break;
    case 'm':
      result = s21_fmod(preLastNumber, lastNumber);
      break;
    default:
      break;
  }
  return result;
}

/// @brief Вычисление унарных функций
/// @param arg аргумент функции
/// @param operation сама функция
/// @return результат функции
double unarOperation(double arg, char operation) {
  double result = 0;
  switch (operation) {
    case 's':
      result = sin(arg);
      result = ifLessEps(result);
      break;

    case 'c':
      result = cos(arg);
      result = ifLessEps(result);
      break;

    case 't':
      result = tan(arg);
      result = ifLessEps(result);
      break;

    case 'y':
      result = asin(arg);
      result = ifLessEps(result);
      break;

    case 'u':
      result = acos(arg);
      result = ifLessEps(result);
      break;

    case 'i':
      result = atan(arg);
      result = ifLessEps(result);
      break;

    case 'q':
      result = sqrt(arg);
      break;

    case 'n':
      result = log(arg);
      break;

    case 'g':
      result = log10(arg);
      break;

    case '~':
      result = -1 * arg;
      break;

    case '@':
      result = arg;
      break;

    default:
      break;
  }
  return result;
}

/// @brief Функция ищет приоритет какой-либо операции, они записаны подряд в
/// массиве char
/// @param sym оператор
/// @return его приоритет
int findPriority(char sym) {
  char result = '0';

  const char priority[40] = {
      '+', '-', '*', '/', 'm', '^', '~', '@', 's', 'c', 't', 'y', 'u', 'i', 'q',
      'n', 'g', '(', ')', 'X', '6', '6', '5', '5', '5', '3', '4', '4', '2',
      '2',  //'6', '6', '5', '5', '5', '3',
            //'4', '4', '2', '2' //'6', '6',
            //'5', '5', '5', '4', '3', '3',
            //'2', '2',
      '2', '2', '2', '2', '2', '2', '2', '7', '7', '1'};  // ( - 0 ) - 1
  for (int i = 0; i <= 19; i++) {
    if (sym == priority[i]) {
      result = priority[i + 20];
      break;
    }
  }
  return result - '0';
}

/// @brief Функция s21_fmod предназначена для вычисления остатка от деления
/// одного числа на другое, аналогично стандартной функции fmod из библиотеки C.
/// Эта функция принимает два аргумента типа double и возвращает результат в
/// виде double
/// @param x первый аргумент функции, число, от которого вы хотите найти остаток
/// @param y второй аргумент функции, число, на которое делится x
/// @return Результат вычисления остатка от деления x на y.
double s21_fmod(double x, double y) {
  double result;
  if (y == 0.0) {
    result = (0.0 / 0.0);
  } else if (y == (1.0 / 0.0) || y == (-1.0 / 0.0)) {
    result = x;
  } else {
    if (x / y < 0) {
      result = x - ceil(x / y) * y;
    } else {
      result = x - floor(x / y) * y;
    }
  }
  return result;
}

/// @brief Добавление в стек операторов новых элементов, а также их исполнение.
/// Если в стеке операторов нет элементов или текущий оператор - открывающая
/// скобка, просто записываем в стек. В ином случае - смотрим на приоритет
/// текущей операции. Если он >= приоритету последней операции в стеке, то
/// проводим операции в стеке, пока это условие истинно, а затем записываем
/// текущий оператор в стек.
/// @param sym текущий оператор, если \0, значит строка закончилась, и считаем
/// всё оставшееся в стеке операторов
/// @param numbersStack стек чисел
/// @param symStack стек операторов
void polshCalculate(char sym, stack **numbersStack, stack **symStack) {
  if (*symStack == NULL || sym == '(') {  //* условие когда кладём в стек
    pushStack(symStack, 0, sym);
  } else {
    if ((findPriority(sym) >= findPriority((*symStack)->sym) || sym == '\0') &&
        sym != ')') {
      do {
        if ((sym == '^' && ((*symStack)->sym) == '^'))
          continue;  /// если две степени идут подряд, нужно чтобы вторая не
                     /// считалась, а записывалась в стек до момента, пока
                     /// степени не закончатся, только затем вынимаем степени по
                     /// одной и вычисляем

        if (findPriority((*symStack)->sym) == 2 || (*symStack)->sym == '~' ||
            (*symStack)->sym == '@') {
          stackUnarOperation(numbersStack, symStack);
        } else {
          stackDoubleOperation(numbersStack, symStack);
        }

      } while ((*symStack) != NULL &&
               findPriority(sym) >= findPriority((*symStack)->sym) &&
               sym != '^');
      // повторяем пока приоритет текущего оператора >=
      // последнему в стеке, но ^ считаются справа
      // налево, поэтому исключение
      if (sym != '\0')
        pushStack(symStack, 0, sym);  // кладём текущий оператор в стек только
                                      // пока строка не закончилась
    } else {
      if (sym == ')') {  // встретили закрытую скобку

        while ((*symStack)->sym !=
               '(') {  // выполняем операции, пока не встретим открывающую

          if (findPriority((*symStack)->sym) == 2 || (*symStack)->sym == '~' ||
              (*symStack)->sym == '@') {
            stackUnarOperation(numbersStack, symStack);

          } else {
            stackDoubleOperation(numbersStack, symStack);
          }
        }

        popStack(symStack);  // удаление открывающей скобки

        if ((*symStack) != NULL &&
            (*symStack)->sym ==
                '~') {  // если перед скобкой стоял унарный минус
          (*numbersStack)->number = ((*numbersStack)->number) * (-1);
          popStack(symStack);  // удаление унарного минуса
        }

      } else if (findPriority(sym) < findPriority((*symStack)->sym)) {
        pushStack(symStack, 0,
                  sym);  // если приоритет текущего оператора < последнего в
                         // стеке, просто его добавляем в стек
      }
    }
  }
}

double ifLessEps(double res) { return fabs(res) < epsl ? 0 : res; }