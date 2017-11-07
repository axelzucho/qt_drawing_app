#include "cone.h"
#include "ui_cone.h"
#include "drawing_points.h"
#include "arco.h"

#define PI 3.14159265

Cone::Cone(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cone)
{
    ui->setupUi(this);
}

Cone::~Cone()
{
    delete ui;
}

void Cone::placePoints(Drawing_Points &dpfile, int startingX, int startingY, int height, int radius) {
    int index = 0;
    Arco arc;
    arc.placePoints(dpfile,radius,radius,startingX,startingY + height);
    dpfile.line = true;
    dpfile.line_number = 2;
    dpfile.line_to_draw[0].setX(startingX);
    dpfile.line_to_draw[0].setY(startingY);
    dpfile.line_to_draw[1].setX(startingX - radius);
    dpfile.line_to_draw[1].setY(startingY + height);
    dpfile.line_to_draw[2].setX(startingX);
    dpfile.line_to_draw[2].setY(startingY);
    dpfile.line_to_draw[3].setX(startingX + radius);
    dpfile.line_to_draw[3].setY(startingY + height);
}
void Cone::on_pushButton_clicked()
{
    Drawing_Points drawing_points;
    int startX = ui->X_TopPoint->value();
    int startY = ui->Y_TopPoint->value();
    int height = ui->Height->value();
    int radius = ui->Radius->value();
    placePoints(drawing_points, startX, startY, height, radius);
    drawing_points.setModal(1);
    drawing_points.exec();
}

void Cone::on_pushButton_2_clicked()
{
    Drawing_Points drawing_points;
    int startX = ui->X_TopPoint->value();
    int startY = ui->Y_TopPoint->value();
    int height = ui->Height->value();
    int radius = ui->Radius->value();
    float x_t = ui->X_Translation->text().toFloat();
    float y_t = ui->Y_Translation->text().toFloat();
    placePoints(drawing_points,startX,startY,height, radius);
    for(int i = 0; i < drawing_points.points_number; ++i) {
        drawing_points.points_to_draw[i].setX(drawing_points.points_to_draw[i].x() + x_t);
        drawing_points.points_to_draw[i].setY(drawing_points.points_to_draw[i].y() + y_t);
    }
    for(int i = 0; i < drawing_points.line_number*2; ++i) {
        drawing_points.line_to_draw[i].setX(drawing_points.line_to_draw[i].x() + x_t);
        drawing_points.line_to_draw[i].setY(drawing_points.line_to_draw[i].y() + y_t);
    }

    drawing_points.setModal(1);
    drawing_points.exec();
}

void Cone::on_drawRotated_clicked()
{
    Drawing_Points drawing_points;
    int startX = ui->X_TopPoint->value();
    int startY = ui->Y_TopPoint->value();
    int height = ui->Height->value();
    int radius = ui->Radius->value();
    float angle = ui->Rotating_Angle->text().toFloat() * PI / 180;
    float x_r = ui->X_Rotating_Point->text().toFloat();
    float y_r = ui->Y_Rotating_Point->text().toFloat();
    placePoints(drawing_points,startX,startY,height, radius);
    for(int i = 0; i < drawing_points.points_number; ++i) {
        drawing_points.points_to_draw[i].setX(x_r + (drawing_points.points_to_draw[i].x() - x_r) * cos(angle) - (drawing_points.points_to_draw[i].y() - y_r) * sin(angle));
        drawing_points.points_to_draw[i].setY(y_r + (drawing_points.points_to_draw[i].x() - x_r) * sin(angle) + (drawing_points.points_to_draw[i].y() - y_r) * cos(angle));
    }
    for(int i = 0; i < drawing_points.line_number*2; ++i) {
        drawing_points.line_to_draw[i].setX(x_r + (drawing_points.line_to_draw[i].x() - x_r) * cos(angle) - (drawing_points.line_to_draw[i].y() - y_r) * sin(angle));
        drawing_points.line_to_draw[i].setY(y_r + (drawing_points.line_to_draw[i].x() - x_r) * sin(angle) + (drawing_points.line_to_draw[i].y() - y_r) * cos(angle));
    }

    drawing_points.setModal(1);
    drawing_points.exec();
}

void Cone::on_drawScaled_clicked()
{
    Drawing_Points drawing_points;
    int startX = ui->X_TopPoint->value();
    int startY = ui->Y_TopPoint->value();
    int height = ui->Height->value();
    int radius = ui->Radius->value();
    float x_scale = ui->X_Scale_Factor->text().toFloat();
    float y_scale = ui->Y_Scale_Factor->text().toFloat();
    placePoints(drawing_points,startX,startY,height, radius);
    for(int i = 0; i < drawing_points.points_number; ++i) {
        drawing_points.points_to_draw[i].setX(drawing_points.points_to_draw[i].x()*x_scale);
        drawing_points.points_to_draw[i].setY(drawing_points.points_to_draw[i].y()*y_scale);
    }
    for(int i = 0; i < drawing_points.line_number*2; ++i) {
        drawing_points.line_to_draw[i].setX(drawing_points.line_to_draw[i].x()*x_scale);
        drawing_points.line_to_draw[i].setY(drawing_points.line_to_draw[i].y()*y_scale);
    }
    drawing_points.setModal(1);
    drawing_points.exec();
}

void Cone::on_drawReflected_clicked()
{
    QString tex = ui->Reflection_Type->currentText();
    Drawing_Points drawing_points;
    int startX = ui->X_TopPoint->value();
    int startY = ui->Y_TopPoint->value();
    int height = ui->Height->value();
    int radius = ui->Radius->value();
    placePoints(drawing_points,startX,startY,height, radius);
    float pos = ui->Reflection->text().toFloat();
    if(tex == "Vertical"){
        for(int i = 0; i < drawing_points.points_number; ++i) {
            drawing_points.points_to_draw[i].setX(2*pos - drawing_points.points_to_draw[i].x());
        }
        for(int i = 0; i < drawing_points.line_number*2; ++i) {
            drawing_points.line_to_draw[i].setX(2*pos - drawing_points.line_to_draw[i].x());
        }
    }
    else if(tex == "Horizontal"){
        for(int i = 0; i < drawing_points.points_number; ++i) {
            drawing_points.points_to_draw[i].setY(2*pos - drawing_points.points_to_draw[i].y());
        }
        for(int i = 0; i < drawing_points.line_number*2; ++i) {
            drawing_points.line_to_draw[i].setY(2*pos - drawing_points.line_to_draw[i].y());
        }
    }

    drawing_points.setModal(1);
    drawing_points.exec();
}
