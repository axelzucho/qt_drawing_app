#include "cone.h"
#include "ui_cone.h"

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
