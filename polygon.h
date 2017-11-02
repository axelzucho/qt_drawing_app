#ifndef POLYGON_H
#define POLYGON_H

#include <QDialog>

namespace Ui {
class Polygon;
}

class Polygon : public QDialog
{
    Q_OBJECT

public:
    explicit Polygon(QWidget *parent = 0);
    ~Polygon();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Polygon *ui;
};

#endif // POLYGON_H
