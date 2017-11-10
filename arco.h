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
    void placeRealPoints(Drawing_Points &dpfile, int centerX, int centerY, float startAngle, float endAngle, int radius);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_drawRotated_clicked();

    void on_drawScaled_clicked();

    void on_drawReflected_clicked();

private:
    Ui::Arco *ui;
};

#endif // ARCO_H
