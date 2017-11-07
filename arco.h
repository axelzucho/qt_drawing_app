#ifndef ARCO_H
#define ARCO_H

#include <QDialog>
#include "drawing_points.h"

namespace Ui {
class Arco;
}

class Arco : public QDialog
{
    Q_OBJECT

public:
    explicit Arco(QWidget *parent = 0);
    ~Arco();
    void placePoints(Drawing_Points &dpfile, int radioX, int radioY, int centerX, int centerY);
    void placeDifferent(Drawing_Points &dpfile, int x, int y, int tras_x, int tras_y, int index);
    void limitAngles(Drawing_Points &dpfile, int radioX, int radioY, int centerX, int centerY);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Arco *ui;
};

#endif // ARCO_H
