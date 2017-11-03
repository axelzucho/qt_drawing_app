#include "rectangularprism.h"
#include "ui_rectangularprism.h"

#define PI 3.14159265

RectangularPrism::RectangularPrism(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RectangularPrism)
{
    ui->setupUi(this);
}

RectangularPrism::~RectangularPrism()
{
    delete ui;
}

void RectangularPrism::drawRectangle(DrawingPolygon& dpfile, int startingX, int startingY, int height, int width, int index)
{
    //Left Vertical line
    dpfile.points_to_draw[index].setX(startingX);
    dpfile.points_to_draw[index++].setY(startingY);
    dpfile.points_to_draw[index].setX(startingX);
    dpfile.points_to_draw[index++].setY(startingY+height);

    //Top Horizontal line
    dpfile.points_to_draw[index].setX(startingX);
    dpfile.points_to_draw[index++].setY(startingY);
    dpfile.points_to_draw[index].setX(startingX+width);
    dpfile.points_to_draw[index++].setY(startingY);

    //Right Vertical line
    dpfile.points_to_draw[index].setX(startingX+width);
    dpfile.points_to_draw[index++].setY(startingY);
    dpfile.points_to_draw[index].setX(startingX+width);
    dpfile.points_to_draw[index++].setY(startingY+height);

    //Bottom Horizontal line
    dpfile.points_to_draw[index].setX(startingX);
    dpfile.points_to_draw[index++].setY(startingY+height);
    dpfile.points_to_draw[index].setX(startingX+width);
    dpfile.points_to_draw[index++].setY(startingY+height);
}

void RectangularPrism::uniteRectangles(DrawingPolygon& dpfile, int startingX, int startingY, int height, int width, int length, int index)
{
    dpfile.points_to_draw[index].setX(startingX);
    dpfile.points_to_draw[index++].setY(startingY);
    dpfile.points_to_draw[index].setX(startingX+length);
    dpfile.points_to_draw[index++].setY(startingY+length);

    dpfile.points_to_draw[index].setX(startingX + width);
    dpfile.points_to_draw[index++].setY(startingY);
    dpfile.points_to_draw[index].setX(startingX + length + width);
    dpfile.points_to_draw[index++].setY(startingY + length);

    dpfile.points_to_draw[index].setX(startingX);
    dpfile.points_to_draw[index++].setY(startingY + height);
    dpfile.points_to_draw[index].setX(startingX + length);
    dpfile.points_to_draw[index++].setY(startingY+ length + height);

    dpfile.points_to_draw[index].setX(startingX + width);
    dpfile.points_to_draw[index++].setY(startingY + height);
    dpfile.points_to_draw[index].setX(startingX + length + width);
    dpfile.points_to_draw[index++].setY(startingY + length + height);
}

void RectangularPrism::placePoints(DrawingPolygon& dpfile, int startingX, int startingY, int height, int width, int length)
{
    dpfile.points_number = 24;
    int index = 0;
    drawRectangle(dpfile,startingX,startingY,height, width, index);
    index += 8;
    drawRectangle(dpfile,startingX+length,startingY + length, height, width, index);
    index += 8;
    uniteRectangles(dpfile,startingX,startingY,height, width,length,index);
}

void RectangularPrism::on_pushButton_clicked()
{
    DrawingPolygon drawingpolygon;
    int startX = ui->X_StartingPoint->value();
    int startY = ui->Y_StartingPoint->value();
    int height = ui->Height->value();
    int width = ui->Width->value();
    int length = ui->Length->value();
    placePoints(drawingpolygon,startX,startY,height,width,length);
    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}

void RectangularPrism::on_pushButton_2_clicked()
{
    DrawingPolygon drawingpolygon;
    int startX = ui->X_StartingPoint->value();
    int startY = ui->Y_StartingPoint->value();
    int height = ui->Height->value();
    int width = ui->Width->value();
    int length = ui->Length->value();
    placePoints(drawingpolygon,startX,startY,height,width,length);
    float x_t = ui->X_Translation->text().toFloat();
    float y_t = ui->Y_Translation->text().toFloat();
    for(int i = 0; i < drawingpolygon.points_number; ++i) {
        drawingpolygon.points_to_draw[i].setX(drawingpolygon.points_to_draw[i].x() + x_t);
        drawingpolygon.points_to_draw[i].setY(drawingpolygon.points_to_draw[i].y() + y_t);
    }

    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}

void RectangularPrism::on_drawRotated_clicked()
{
    DrawingPolygon drawingpolygon;
    int startX = ui->X_StartingPoint->value();
    int startY = ui->Y_StartingPoint->value();
    int height = ui->Height->value();
    int width = ui->Width->value();
    int length = ui->Length->value();
    placePoints(drawingpolygon,startX,startY,height,width,length);
    float angle = ui->Rotating_Angle->text().toFloat() * PI / 180;
    float x_r = ui->X_Rotating_Point->text().toFloat();
    float y_r = ui->Y_Rotating_Point->text().toFloat();
    for(int i = 0; i < drawingpolygon.points_number; ++i) {
        drawingpolygon.points_to_draw[i].setX(x_r + (drawingpolygon.points_to_draw[i].x() - x_r) * cos(angle) - (drawingpolygon.points_to_draw[i].y() - y_r) * sin(angle));
        drawingpolygon.points_to_draw[i].setY(y_r + (drawingpolygon.points_to_draw[i].x() - x_r) * sin(angle) + (drawingpolygon.points_to_draw[i].y() - y_r) * cos(angle));
    }

    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}

void RectangularPrism::on_drawScaled_clicked()
{
    DrawingPolygon drawingpolygon;
    int startX = ui->X_StartingPoint->value();
    int startY = ui->Y_StartingPoint->value();
    int height = ui->Height->value();
    int width = ui->Width->value();
    int length = ui->Length->value();
    placePoints(drawingpolygon,startX,startY,height,width,length);
    float x_scale = ui->X_Scale_Factor->text().toFloat();
    float y_scale = ui->Y_Scale_Factor->text().toFloat();
    for(int i = 0; i <drawingpolygon.points_number; ++i) {
        drawingpolygon.points_to_draw[i].setX(drawingpolygon.points_to_draw[i].x()*x_scale);
        drawingpolygon.points_to_draw[i].setY(drawingpolygon.points_to_draw[i].y()*y_scale);
    }
    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}

void RectangularPrism::on_drawReflected_clicked()
{
    QString tex = ui->Reflection_Type->currentText();
    DrawingPolygon drawingpolygon;
    int startX = ui->X_StartingPoint->value();
    int startY = ui->Y_StartingPoint->value();
    int height = ui->Height->value();
    int width = ui->Width->value();
    int length = ui->Length->value();
    placePoints(drawingpolygon,startX,startY,height,width,length);
    float pos = ui->Reflection->text().toFloat();
    if(tex == "Vertical"){
        for(int i = 0; i < drawingpolygon.points_number; ++i) {
            drawingpolygon.points_to_draw[i].setX(2*pos - drawingpolygon.points_to_draw[i].x());
        }
    }
    else if(tex == "Horizontal"){
        for(int i = 0; i < drawingpolygon.points_number; ++i) {
            drawingpolygon.points_to_draw[i].setY(2*pos - drawingpolygon.points_to_draw[i].y());
        }
    }

    drawingpolygon.setModal(1);
    drawingpolygon.exec();
}


