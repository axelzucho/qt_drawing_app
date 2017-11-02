#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygon.h"
#include "arco.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonClose_clicked()
{

}

void MainWindow::on_pushButton_clicked()
{
    Polygon polygon;
    polygon.setModal(true);
    polygon.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    Arco arco;
    arco.setModal(1);
    arco.exec();
}
