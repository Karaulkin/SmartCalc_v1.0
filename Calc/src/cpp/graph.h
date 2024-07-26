#ifndef GRAPH_H
#define GRAPH_H

#include <QDebug>
#include <QDialog>
#include <QVector>
#include <iostream>

#include "mainwindow.h"
#include "qcustomplot.h"
#include "ui_graph.h"

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

#include "../deposit/depositCalculation.h"

#ifdef __cplusplus
}
#endif  // __cplusplus

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr, QString a = "");
  ~Graph();
  Ui::Graph *ui;
  QString *graph;
  QString expression = "";

 private slots:
  // void on_pushButton_2_clicked();
  void on_pushButton_clicked();

 private:
  double xBegin = 0, xEnd, h = 0, X = 0,
         Y = 0;  // область отображения X, h - шаг между двумя точками, X -
                 // заполнение вектора

  int N = 0;  // кол-во точек

  void reloadSize();
  void printGraph(QString strX, QString str);

  QVector<double> x = {0}, y = {0};

  int errorGraph = 0;
};

#endif  // GRAPH_H
