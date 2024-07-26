/**
 * @file s21_SmartCalc_v1.0.h
 * @brief Заголовочный файл, описывающий библиотеки, использующиеся при
 * счёте математического калькулятора написанного на C
 */

#ifndef __S21_SMART_CALC_v1_0__
#define __S21_SMART_CALC_v1_0__
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.1415926535897932384626433832795028841971
#define E 2.7182818284590452353602874713526624977572
#define epsl 1e-10

/// @brief Структура stack предназначениая для реализации стека суммы чисел и
/// стека операторов
/// @param sym переменная для стэка операций (символов)
/// @param number переменная для стэка чисел
/// @param next указатель на следующий элемент стека
typedef struct stack {
  char sym;
  long double number;
  struct stack *next;
} stack;

/// @brief Структура errorsVariables предназначенна для счёта открывающихся,
/// закрывающихся скобок и счёта количества точек в числе
/// @param countBeginBrackets это поле предназначено для подсчета количества
/// открывающих скобок '(' в выражении
/// @param countEndBrackets это поле предназначено для подсчета количества
/// закрывающих скобок ')' в выражении
/// @param dotFlag это поле используется для отслеживания наличия точки (.) в
/// выражении
typedef struct errorsVariables {
  int countBeginBrackets;
  int countEndBrackets;
  int dotFlag;
} errorsVariables;

/*
  Сокращения функций:
  sin - s
  cos - c
  tan - t
  asin - y
  acos - u
  atan - i
  sqrt - q
  ln - n
  log - g
  mod - m
  unar- - ~
  unar+ - @
*/

double calculation(char *strIn, char *X, int *error);
void allocateSpace(char **str);
void freeSpace(char **str);

void pushStack(stack **top, double number, char sym);
void popStack(stack **top);
void freeStack(stack **top);

int checkVal(char val);
char *parserCoder(char *strIn, char *strOut, char *X, int *error);
void parserUnarMin(char *strIn, char *strOut, int *i, int j);
void parserUnarPlus(char *strIn, char *strOut, int *i, int *j);
void parserX(char *strOut, int *j, char *X, int *error);
void parserSinSqrt(char *strIn, char *strOut, int *i, int j, int *error);
void parserCos(char *strIn, char *strOut, int *i, int j, int *error);
void parserTan(char *strIn, char *strOut, int *i, int j, int *error);
void parserAsinAcosAtan(char *strIn, char *strOut, int *i, int j, int *error);
void parserLogLn(char *strIn, char *strOut, int *i, int j, int *error);
void parserMod(char *strIn, char *strOut, int *i, int j, int *error);

int isNumberDot(char n);
void parserOfStacks(char *strOut, stack **numbersStack, stack **symStack);
double parserNumber(char *strOut, int *i);

void polshCalculate(char sym, stack **numbersStack, stack **symStack);
double doubleOperation(double lastNumber, double preLastNumber, char operation);
double unarOperation(double lastNumber, char operation);
void stackUnarOperation(stack **numbersStack, stack **symStack);
void stackDoubleOperation(stack **numbersStack, stack **symStack);
double s21_fmod(double x, double y);
double ifLessEps(double res);
int findPriority(char sym);

int mathCheckStr(char *str);
int startsWithZero(char *input);

#endif  // __S21_SMART_CALC_v1_0__