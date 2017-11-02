#ifndef DRAWINGPOLYGON_H
#define DRAWINGPOLYGON_H

#include <QDialog>

namespace Ui {
class DrawingPolygon;
}

class DrawingPolygon : public QDialog
{

    Q_OBJECT

public:
    int points_number;
    QPointF points_to_draw[20];
    explicit DrawingPolygon(QWidget *parent = 0);
    ~DrawingPolygon();
    void paintEvent(QPaintEvent *event);

private:
    Ui::DrawingPolygon *ui;
};

#endif // DRAWINGPOLYGON_H
