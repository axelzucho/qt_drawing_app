#include "arco.h"
#include "ui_arco.h"
#include "drawing_points.h"
#include "math.h"

#define PI 3.14159265

Arco::Arco(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Arco)
{
    ui->setupUi(this);
}

Arco::~Arco()
{
    delete ui;
}

void Arco::placeDifferent(Drawing_Points &dpfile, int x, int y, int tras_x, int tras_y, int index) {
    dpfile.points_to_draw[index].setX(tras_x + x);
    dpfile.points_to_draw[index++].setY(tras_y + y);
    dpfile.points_to_draw[index].setX(tras_x + x);
    dpfile.points_to_draw[index++].setY(tras_y - y);
    dpfile.points_to_draw[index].setX(tras_x - x);
    dpfile.points_to_draw[index++].setY(tras_y + y);
    dpfile.points_to_draw[index].setX(tras_x - x);
    dpfile.points_to_draw[index++].setY(tras_y - y);
}

void Arco::placePoints(Drawing_Points &dpfile, int radioX, int radioY, int centerX, int centerY)
{
    int x = 0, y = radioY;
    int index = 0;
    int p, pe, pse, two_pe, two_pse;
    p = radioY*radioY + (radioX*radioX*(1-4*radioY) - 2) / 4;
    pe = 3*radioY*radioY;
    two_pe = 2*radioY*radioY;
    pse = pe - 2*radioX*radioX*(radioY-1);
    two_pse = two_pe + 2*radioX*radioX;
    placeDifferent(dpfile,x,y,centerX,centerY,index);
    index += 4;
    while(pse < 2*radioX*radioX + 3*radioY*radioY) {
        if (p < 0) {
            p += pe;
            pe += two_pe;
            pse += two_pe;
        }
        else {
            p += pse;
            pe += two_pe;
            pse += two_pse;
            --y;
        }
        ++x;
        placeDifferent(dpfile,x,y,centerX,centerY,index);
        index += 4;
    }
    //Region 2
      p=radioY*radioY*(x+0.5)*(x+0.5)+radioX*radioX*(y-1)*(y-1)-radioX*radioX*radioY*radioY;
      while(y > 0)
      {
       if(p <= 0)
       {
           x++;y--;
           p = p+2*radioY*radioY*x-2*radioX*radioX*y+radioX*radioX;
       }
       else
       {
           y--;
           p = p-2*radioX*radioX*y+radioX*radioX;
       }
            placeDifferent(dpfile,x,y,centerX,centerY,index);
            index += 4;
        }

    dpfile.points_number = index;

    int start_angle = ui->startAngle->value();
    int end_angle = ui->endAngle->value();
    //int checkX1 = centerX + radioX*cos(startAngle), checkX2 = centerX + radioX*cos(endAngle);
    //int checkY1 = centerY + radioY*cos(startAngle), checkY2 = centerY + radioY*cos(endAngle);
    int checkX, checkY;
    for (int i = 0; i < dpfile.points_number; ++i) {
        checkX = acos((dpfile.points_to_draw[i].x() - centerX)/radioX) * 180/PI;
        checkY = acos((dpfile.points_to_draw[i].y() - centerY)/radioY) * 180/PI;
        if(checkX < 0) checkX += 360;
        if(checkY < 0) checkY += 360;
        if(checkX < start_angle || checkX > end_angle || checkY < start_angle || checkY > end_angle) {
        dpfile.points_to_draw[i].setX(1000000);
        dpfile.points_to_draw[i].setY(1000000);
        }
    }
}

void Arco::on_pushButton_clicked()
{
    Drawing_Points drawing_points;
    int radioX = ui->radioX->value();
    int radioY = ui->radioY->value();
    int centerX = ui->centerX->value();
    int centerY = ui->centerY->value();
    placePoints(drawing_points, radioX, radioY, centerX, centerY);
    drawing_points.setModal(1);
    drawing_points.exec();
}
