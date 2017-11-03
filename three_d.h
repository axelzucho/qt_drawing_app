#ifndef THREE_D_H
#define THREE_D_H

#include <QDialog>

namespace Ui {
class Three_D;
}

class Three_D : public QDialog
{
    Q_OBJECT

public:
    explicit Three_D(QWidget *parent = 0);
    ~Three_D();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Three_D *ui;
};

#endif // THREE_D_H
