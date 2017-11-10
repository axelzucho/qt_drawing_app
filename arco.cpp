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
}

void Arco::limitAngles(Drawing_Points &dpfile, int radioX, int radioY, int centerX, int centerY) {
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

void Arco::placeRealPoints(Drawing_Points &dpfile, int centerX, int centerY, float startAngle, float endAngle, int radius) {
    int index = 0;
    startAngle = startAngle *PI/180;
    endAngle = endAngle * PI/180;
    while(startAngle < endAngle) {
        dpfile.points_to_draw[index].setX(centerX + radius*cos(startAngle));
        dpfile.points_to_draw[index++].setY(centerY + radius*sin(startAngle));
        startAngle += 0.001;
    }
    dpfile.points_number = index;
}


void Arco::on_pushButton_clicked()
{
    Drawing_Points drawing_points;
    int radius = ui->radius->value();
    int centerX = ui->centerX->value();
    int centerY = ui->centerY->value();
    float startAngle = ui->startAngle->value();
    float endAngle= ui->endAngle->value();
    placeRealPoints(drawing_points,centerX,centerY,startAngle,endAngle,radius);
    drawing_points.setModal(1);
    drawing_points.exec();
}


void Arco::on_pushButton_2_clicked()
{
    Drawing_Points drawing_points;
    int radius = ui->radius->value();
    int centerX = ui->centerX->value();
    int centerY = ui->centerY->value();
    float startAngle = ui->startAngle->value();
    float endAngle= ui->endAngle->value();
    placeRealPoints(drawing_points,centerX,centerY,startAngle,endAngle,radius);
    float x_t = ui->X_Translation->text().toFloat();
    float y_t = ui->Y_Translation->text().toFloat();
    for(int i = 0; i < drawing_points.points_number; ++i) {
        drawing_points.points_to_draw[i].setX(drawing_points.points_to_draw[i].x() + x_t);
        drawing_points.points_to_draw[i].setY(drawing_points.points_to_draw[i].y() + y_t);
    }

    drawing_points.setModal(1);
    drawing_points.exec();
}

void Arco::on_drawRotated_clicked()
{
    Drawing_Points drawing_points;
    int radius = ui->radius->value();
    int centerX = ui->centerX->value();
    int centerY = ui->centerY->value();
    float startAngle = ui->startAngle->value();
    float endAngle= ui->endAngle->value();
    placeRealPoints(drawing_points,centerX,centerY,startAngle,endAngle,radius);
    float angle = ui->Rotating_Angle->text().toFloat() * PI / 180;
    float x_r = ui->X_Rotating_Point->text().toFloat();
    float y_r = ui->Y_Rotating_Point->text().toFloat();
    for(int i = 0; i < drawing_points.points_number; ++i) {
        drawing_points.points_to_draw[i].setX(x_r + (drawing_points.points_to_draw[i].x() - x_r) * cos(angle) - (drawing_points.points_to_draw[i].y() - y_r) * sin(angle));
        drawing_points.points_to_draw[i].setY(y_r + (drawing_points.points_to_draw[i].x() - x_r) * sin(angle) + (drawing_points.points_to_draw[i].y() - y_r) * cos(angle));
    }

    drawing_points.setModal(1);
    drawing_points.exec();
}

void Arco::on_drawScaled_clicked()
{
    Drawing_Points drawing_points;
    int radius = ui->radius->value();
    int centerX = ui->centerX->value();
    int centerY = ui->centerY->value();
    float startAngle = ui->startAngle->value();
    float endAngle= ui->endAngle->value();
    placeRealPoints(drawing_points,centerX,centerY,startAngle,endAngle,radius);
    float x_scale = ui->X_Scale_Factor->text().toFloat();
    float y_scale = ui->Y_Scale_Factor->text().toFloat();
    for(int i = 0; i <drawing_points.points_number; ++i) {
        drawing_points.points_to_draw[i].setX(drawing_points.points_to_draw[i].x()*x_scale);
        drawing_points.points_to_draw[i].setY(drawing_points.points_to_draw[i].y()*y_scale);
    }
    drawing_points.setModal(1);
    drawing_points.exec();
}

void Arco::on_drawReflected_clicked()
{
    QString tex = ui->Reflection_Type->currentText();
    Drawing_Points drawing_points;
    int radius = ui->radius->value();
    int centerX = ui->centerX->value();
    int centerY = ui->centerY->value();
    float startAngle = ui->startAngle->value();
    float endAngle= ui->endAngle->value();
    placeRealPoints(drawing_points,centerX,centerY,startAngle,endAngle,radius);
    float pos = ui->Reflection->text().toFloat();
    if(tex == "Vertical"){
        for(int i = 0; i < drawing_points.points_number; ++i) {
            drawing_points.points_to_draw[i].setX(2*pos - drawing_points.points_to_draw[i].x());
        }
    }
    else if(tex == "Horizontal"){
        for(int i = 0; i < drawing_points.points_number; ++i) {
            drawing_points.points_to_draw[i].setY(2*pos - drawing_points.points_to_draw[i].y());
        }
    }

    drawing_points.setModal(1);
    drawing_points.exec();
}
