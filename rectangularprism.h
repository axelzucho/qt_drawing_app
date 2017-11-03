#ifndef RECTANGULARPRISM_H
#define RECTANGULARPRISM_H

#include <QDialog>
#include "drawingpolygon.h"

namespace Ui {
class RectangularPrism;
}

class RectangularPrism : public QDialog
{
    Q_OBJECT

public:
    explicit RectangularPrism(QWidget *parent = 0);
    ~RectangularPrism();
    void drawRectangle(DrawingPolygon& dpfile, int startingX, int startingY, int height, int width, int index);
    void uniteRectangles(DrawingPolygon& dpfile, int startingX, int startingY, int height, int width, int length, int index);
    void placePoints(DrawingPolygon& dpfile, int startingX, int startingY, int height, int width, int length);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_drawRotated_clicked();

    void on_drawScaled_clicked();

    void on_drawReflected_clicked();

private:
    Ui::RectangularPrism *ui;
};

#endif // RECTANGULARPRISM_H
