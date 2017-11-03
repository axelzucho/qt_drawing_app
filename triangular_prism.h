#ifndef TRIANGULAR_PRISM_H
#define TRIANGULAR_PRISM_H

#include "drawingpolygon.h"

#include <QDialog>

namespace Ui {
class Triangular_Prism;
}

class Triangular_Prism : public QDialog
{
    Q_OBJECT

public:
    explicit Triangular_Prism(QWidget *parent = 0);
    ~Triangular_Prism();
    void drawTriangle(DrawingPolygon& dpfile, int startingX, int startingY, int height, int width, int index);
    void uniteTriangles(DrawingPolygon& dpfile, int startingX, int startingY, int height, int width, int length, int index);
    void placePoints(DrawingPolygon& dpfile, int startingX, int startingY, int width, int height, int length);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_drawRotated_clicked();

    void on_drawScaled_clicked();

    void on_drawReflected_clicked();

private:
    Ui::Triangular_Prism *ui;

};

#endif // TRIANGULAR_PRISM_H
