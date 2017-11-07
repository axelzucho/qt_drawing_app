#ifndef CONE_H
#define CONE_H

#include <QDialog>
#include "drawing_points.h"

namespace Ui {
class Cone;
}

class Cone : public QDialog
{
    Q_OBJECT

public:
    explicit Cone(QWidget *parent = 0);
    void placePoints(Drawing_Points& dpfile, int startingX, int startingY, int height, int radius);
    ~Cone();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_drawRotated_clicked();

    void on_drawScaled_clicked();

    void on_drawReflected_clicked();

private:
    Ui::Cone *ui;
};

#endif // CONE_H
