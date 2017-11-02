#include "polygon.h"
#include "ui_polygon.h"
#include "drawingpolygon.h"
#include <math.h>

#define PI 3.14159265

int previous = 0;
int array[20][2];
Polygon::Polygon(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::Polygon)
{
    ui->setupUi(this);
}

Polygon::~Polygon()
{
    delete ui;
}

void Polygon::on_spinBox_valueChanged(int arg1)
{
    if(arg1 > previous) ui->points->insertRow(arg1-1);
    if(arg1 < previous) ui->points->removeRow(previous-1);
    previous = arg1;
}

void Polygon::on_pushButton_clicked()
{
    DrawingPolygon drawingpolygon;
    drawingpolygon.points_number = ui->points->rowCount();
    for(int i = 0; i < ui->points->rowCount(); ++i) {
        //array[i][0] = ui->points->item(i,0)->text().toInt();
        //array[i][1] = (int)ui->points->item(i,1)->text().toInt();
        drawingpolygon.points_to_draw[2*i].setX(ui->points->item(i,0)->text().toFloat());
        drawingpolygon.points_to_draw[2*i].setY(ui->points->item(i,1)->text().toFloat());
        drawingpolygon.points_to_draw[2*i+1].setX(ui->points->item(i,2)->text().toFloat());
        drawingpolygon.points_to_draw[2*i+1].setY(ui->points->item(i,3)->text().toFloat());
    }

    drawingpolygon.setModal(1);
    drawingpolygon.exec();
    //arco.exec();
}

void Polygon::on_pushButton_2_clicked()
{
    float x_t = ui->X_Translation->text().toFloat();
    float y_t = ui->Y_Translation->text().toFloat();
    DrawingPolygon drawingpolygon;
    drawingpolygon.points_number = ui->points->rowCount();
    for(int i = 0; i < ui->points->rowCount(); ++i) {
        drawingpolygon.points_to_draw[2*i].setX(ui->points->item(i,0)->text().toFloat() + x_t);
        drawingpolygon.points_to_draw[2*i].setY(ui->points->item(i,1)->text().toFloat() + y_t);
        drawingpolygon.points_to_draw[2*i+1].setX(ui->points->item(i,2)->text().toFloat() + x_t);
        drawingpolygon.points_to_draw[2*i+1].setY(ui->points->item(i,3)->text().toFloat() + y_t);
    }

    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}

void Polygon::on_pushButton_3_clicked()
{
    float angle = ui->Rotating_Angle->text().toFloat() * PI / 180;
    float x_r = ui->X_Rotating_Point->text().toFloat();
    float y_r = ui->Y_Rotating_Point->text().toFloat();
    DrawingPolygon drawingpolygon;
    drawingpolygon.points_number = ui->points->rowCount();
    for(int i = 0; i < ui->points->rowCount(); ++i) {
        float x0, y0,x1,y1;
        x0 = ui->points->item(i,0)->text().toFloat();
        x1 = ui->points->item(i,2)->text().toFloat();
        y0 = ui->points->item(i,1)->text().toFloat();
        y1 = ui->points->item(i,3)->text().toFloat();
        drawingpolygon.points_to_draw[2*i].setX(x_r + (x0 - x_r) * cos(angle) - (y0 - y_r) * sin(angle));
        drawingpolygon.points_to_draw[2*i].setY(y_r + (x0 - x_r) * sin(angle) + (y0 - y_r) * cos(angle));
        drawingpolygon.points_to_draw[2*i+1].setX(x_r + (x1 - x_r) * cos(angle) - (y1 - y_r) * sin(angle));
        drawingpolygon.points_to_draw[2*i+1].setY(y_r + (x1 - x_r) * sin(angle) + (y1 - y_r) * cos(angle));
    }

    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}

void Polygon::on_pushButton_4_clicked()
{
    DrawingPolygon drawingpolygon;
    drawingpolygon.points_number = ui->points->rowCount();
    float x_scale = ui->X_Scale_Factor->text().toFloat();
    float y_scale = ui->Y_Scale_Factor->text().toFloat();
    for(int i = 0; i < ui->points->rowCount(); ++i) {
        drawingpolygon.points_to_draw[2*i].setX(ui->points->item(i,0)->text().toFloat()*x_scale);
        drawingpolygon.points_to_draw[2*i].setY(ui->points->item(i,1)->text().toFloat()*y_scale);
        drawingpolygon.points_to_draw[2*i+1].setX(ui->points->item(i,2)->text().toFloat()*x_scale);
        drawingpolygon.points_to_draw[2*i+1].setY(ui->points->item(i,3)->text().toFloat()*y_scale);
    }
    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}

void Polygon::on_pushButton_5_clicked()
{
    DrawingPolygon drawingpolygon;
    drawingpolygon.points_number = ui->points->rowCount();
    float pos = ui->Reflection->text().toFloat();
    if(ui->Reflection_Type->itemData(ui->Reflection_Type->currentIndex()) == 'Vertical'){
        for(int i = 0; i < ui->points->rowCount(); ++i) {
            drawingpolygon.points_to_draw[2*i].setX(pos + (pos - ui->points->item(i,0)->text().toFloat()));
            drawingpolygon.points_to_draw[2*i].setY(ui->points->item(i,1)->text().toFloat());
            drawingpolygon.points_to_draw[2*i+1].setX(pos + (pos - ui->points->item(i,2)->text().toFloat()));
            drawingpolygon.points_to_draw[2*i+1].setY(ui->points->item(i,3)->text().toFloat());
        }
    }
    else if(ui->Reflection_Type->itemData(ui->Reflection_Type->currentIndex()) == "Horizontal"){
        for(int i = 0; i < ui->points->rowCount(); ++i) {
            drawingpolygon.points_to_draw[2*i].setX(ui->points->item(i,0)->text().toFloat());
            drawingpolygon.points_to_draw[2*i].setY(2*pos - ui->points->item(i,1)->text().toFloat());
            drawingpolygon.points_to_draw[2*i+1].setX(ui->points->item(i,2)->text().toFloat());
            drawingpolygon.points_to_draw[2*i+1].setY(2*pos - ui->points->item(i,3)->text().toFloat());
        }
    }

    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}
