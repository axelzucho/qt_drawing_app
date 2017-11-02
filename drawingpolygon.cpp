#include "drawingpolygon.h"
#include "ui_drawingpolygon.h"
#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <iostream>



DrawingPolygon::DrawingPolygon(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DrawingPolygon)
{
    ui->setupUi(this);
    /*QPicture pi;
    QPainter painter(&pi);
            painter.setPen(QPen(Qt::black, 12, Qt::DashDotLine, Qt::RoundCap));
            painter.drawLines(points_to_draw,points_number);
            //std::cout << "Entro";
            QLabel l;
            painter.end();
            l.setPicture(pi);
            l.show();*/
    //paintEvent();

}

DrawingPolygon::~DrawingPolygon()
{
    delete ui;
}

void DrawingPolygon::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap));
    painter.drawLines(points_to_draw,points_number);
}
