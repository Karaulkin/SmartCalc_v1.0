#include "graph.h"

Graph::Graph(QWidget *parent, QString str)
    : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  setWindowFlags(
      Qt::Dialog |
      Qt::MSWindowsFixedSizeDialogHint);  // для ограничения расширения окна
  // reloadSize();

  // qDebug() << str;

  // QString toStr = QString::number(xBegin, 'g', 7);

  // qDebug() << toStr;

  // printGraph(toStr, str);
  connect(ui->pushButton_Build, SIGNAL(clicked()), this,
          SLOT(on_pushButton_clicked()));
}

Graph::~Graph() { delete ui; }

void Graph::on_pushButton_clicked() {
  expression = ui->label_text->text();

  reloadSize();

  QString toStr = QString::number(xBegin, 'g', 7);
  printGraph(toStr, expression);
}

void Graph::printGraph(QString strX, QString str) {  // подизменить
  for (X = xBegin; X <= xEnd; X += h) {
    if (X < 0.1 && X > -0.1)  // ?
      X = 0;
    strX = QString::number(X, 'g', 7);
    Y = calculation(str.toUtf8().data(), strX.toUtf8().data(),
                    &errorGraph);  // не считает
    if (errorGraph == 0) {
      x.push_back(X);
      y.push_back(Y);
    } else {
      ui->label_text->setText(
          QString("В точке {%1} произошла ошибка\nвычисления: err %2")
              .arg(X)
              .arg(errorGraph));
    }
    errorGraph = 0;
  }
  // удиление самого первого элемента массива
  x.remove(0);
  y.remove(0);

  ui->widget_graph->addGraph();
  ui->widget_graph->graph(0)->addData(x, y);
  ui->widget_graph->replot();
}

void Graph::reloadSize() {
  h = ui->doubleSpinBox_eps->value();

  xBegin = ui->doubleSpinBox_leftX->value();
  xEnd = ui->doubleSpinBox_rightX->value() + h;

  ui->widget_graph->xAxis->setRange(
      ui->doubleSpinBox_leftX->value() - 5,
      ui->doubleSpinBox_rightX->value() + 5);  // Задать ширину
  ui->widget_graph->yAxis->setRange(ui->doubleSpinBox_lowY->value() - 5,
                                    ui->doubleSpinBox_topY->value() + 5);

  ui->widget_graph->xAxis->setLabel("x");
  ui->widget_graph->yAxis->setLabel("y");

  N = (xEnd - xBegin) / h + 2;
}
