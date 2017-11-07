#ifndef DRAWING_POINTS_H
#define DRAWING_POINTS_H

#include <QDialog>

namespace Ui {
class Drawing_Points;
}

class Drawing_Points : public QDialog
{
    Q_OBJECT

public:
    int points_number;
    QPointF points_to_draw[10000];
    bool line;
    QPointF line_to_draw[10000];
    int line_number;
    explicit Drawing_Points(QWidget *parent = 0);
    ~Drawing_Points();
    void paintEvent(QPaintEvent *event);
private:
    Ui::Drawing_Points *ui;
};

#endif // DRAWING_POINTS_H
