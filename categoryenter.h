#ifndef CATEGORYENTER_H
#define CATEGORYENTER_H

#include <QDialog>

namespace Ui {
class CategoryEnter;
}

class CategoryEnter : public QDialog
{
    Q_OBJECT

    QString category;

public:
    explicit CategoryEnter(QWidget *parent = 0);
    ~CategoryEnter();

    QString getCategory();

private slots:
    void on_btnOK_clicked();

private:
    Ui::CategoryEnter *ui;
};

#endif // CATEGORYENTER_H
