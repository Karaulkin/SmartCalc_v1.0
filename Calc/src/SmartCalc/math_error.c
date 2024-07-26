#include "s21_SmartCalc_v1.0.h"

/// @brief Функция находит математические ошибки напечатанные пользователем
/// @param str массив символов представлющий строку (математическое выражение)
/// @return возвращает "0", если в входной строке не было найденно ошибок
int mathCheckStr(char *str) {
  int res = 0;
  errorsVariables errors = {0};

  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] == '(') errors.countBeginBrackets++;

    if (str[i] == ')') errors.countEndBrackets++;

    if (str[i] >= '0' && str[i] <= '9') {
      if (startsWithZero(str + i) == 1 && (str[i + 1] != '.')) {
        if (!(str[i - 1] >= '0' && str[i - 1] >= '9') &&
            (str[i + 1] >= '0' && str[i + 1] >= '9'))
          res = 15;  //Целое число не может начинаться с нуля

      } else if ((str[i] != '\0' && isNumberDot(str[i + 1]) == 0 &&
                  isNumberDot(str[i]) == 1 &&
                  (findPriority(str[i + 1]) == 2 || str[i + 1] == '(' ||
                   str[i + 1] == '~' || str[i + 1] == '@')) ||
                 (i != 0 && str[i - 1] == ')' &&
                  (isNumberDot(str[i]) == 1 || isNumberDot(str[i]) == 3))) {
        res = 16;  // Нет оператора между числом и функцией!

      } else {
        errors.dotFlag = 0;

        while (isNumberDot(str[i]) == 1 || isNumberDot(str[i]) == 2) {
          if (isNumberDot(str[i]) == 2 && errors.dotFlag == 0)
            errors.dotFlag = 1;

          else if (isNumberDot(str[i]) == 2 && errors.dotFlag == 1) {
            res = 8;  // В дробном числе слишком много точек
          }
          i++;
        }

        i--;
      }
    } else if (str[i] != '\0' && isNumberDot(str[i]) == 0 &&
               isNumberDot(str[i + 1]) == 0 &&
               (findPriority(str[i + 1]) > 3 && str[i + 1] != '~' &&
                str[i + 1] != '@') &&
               str[i] != '(' && str[i] != ')' && str[i + 1] != '(' &&
               str[i + 1] != ')') {
      res = 9;  // Два оператора не могут стоять рядом!

    } else if (str[i] != '\0' && ((str[i] == '(' && str[i + 1] == ')') ||
                                  (str[i] == ')' && str[i + 1] == '('))) {
      res = 10;  // Пустые скобки не могут быть!

    } else if (str[i] == '(' && (isNumberDot(str[i + 1]) == 0) &&
               (findPriority(str[i + 1]) > 3 && str[i + 1] != '~' &&
                str[i + 1] != '@') &&
               str[i + 1] != '(' && str[i + 1] != '-') {
      res = 11;  // После открывающей скобки не может быть оператора, кроме

      // минуса
    } else if (((i != 0 && isNumberDot(str[i - 1]) != 1) || (i == 0)) &&
               str[i] == '.') {
      res = 12;  // Число не может начинаться с точки

    } else if (i != 0 && str[i] == '(' && isNumberDot(str[i - 1]) != 0) {
      res = 13;  // Перед открывающей скобкой должен быть оператор
    }
  }
  if (errors.countBeginBrackets != errors.countEndBrackets)
    res = 14;  // Колличество открывающих и закрывающих скобок не тождественно

  return res;
}

/// @brief Функция startsWithZero проверяет, начинается ли первое число в
/// заданной строке с нуля.
/// @param input указатель на входную строку, в которой нужно проверить,
/// начинается ли первое число с нуля.
/// @return Функция startsWithZero возвращает 1 (истина), если первое число в
/// заданной строке начинается с нуля, и 0 (ложь) в противном случае.
int startsWithZero(char *input) {
  // Находим первое число в строке
  char *start = strpbrk(input, "0123456789");
  if (start != NULL) {
    // Проверяем, начинается ли число с нуля
    return *start == '0';
  }
  return 0;  // Нет чисел в строке
}