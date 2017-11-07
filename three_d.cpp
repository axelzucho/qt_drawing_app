#include "three_d.h"
#include "ui_three_d.h"
#include "cube.h"
#include "rectangularprism.h"
#include "triangular_prism.h"
#include "cone.h"

Three_D::Three_D(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Three_D)
{
    ui->setupUi(this);
}

Three_D::~Three_D()
{
    delete ui;
}

void Three_D::on_pushButton_clicked()
{
    Cube cube;
    cube.setModal(1);
    cube.exec();
}

void Three_D::on_pushButton_2_clicked()
{
    RectangularPrism rectangular_prism;
    rectangular_prism.setModal(1);
    rectangular_prism.exec();
}

void Three_D::on_pushButton_4_clicked()
{
    Triangular_Prism triangular_prism;
    triangular_prism.setModal(1);
    triangular_prism.exec();
}

void Three_D::on_pushButton_5_clicked()
{
    Cone cone;
    cone.setModal(1);
    cone.exec();
}
