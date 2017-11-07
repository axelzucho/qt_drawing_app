#include "drawing_points.h"
#include "ui_drawing_points.h"
#include <QApplication>
#include <QLabel>
#include <QPicture>
#include <QPainter>
#include <iostream>

Drawing_Points::Drawing_Points(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Drawing_Points)
{
    line = false;
    ui->setupUi(this);
}

Drawing_Points::~Drawing_Points()
{
    delete ui;
}

void Drawing_Points::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawPoints(points_to_draw,points_number);
    if(line) {
        painter.drawLines(line_to_draw,line_number);
    }
}
