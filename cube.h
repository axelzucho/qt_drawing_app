#ifndef CUBE_H
#define CUBE_H

#include <QDialog>
#include "drawingpolygon.h"

namespace Ui {
class Cube;
}

class Cube : public QDialog
{
    Q_OBJECT

public:
    explicit Cube(QWidget *parent = 0);
    ~Cube();
    void drawSquare(DrawingPolygon& dpfile, int startingX, int startingY, int length, int index);
    void uniteSquares(DrawingPolygon& dpfile, int startingX, int startingY, int length, int index);
    void placePoints(DrawingPolygon& dpfile, int startingX, int startingY, int length);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_drawRotated_clicked();

    void on_drawScaled_clicked();

    void on_drawReflected_clicked();

private:
    Ui::Cube *ui;
};

#endif // CUBE_H
