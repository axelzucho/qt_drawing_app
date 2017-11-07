#ifndef CONE_H
#define CONE_H

#include <QDialog>

namespace Ui {
class Cone;
}

class Cone : public QDialog
{
    Q_OBJECT

public:
    explicit Cone(QWidget *parent = 0);
    ~Cone();

private:
    Ui::Cone *ui;
};

#endif // CONE_H
