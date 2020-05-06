#ifndef NAMEENTER_H
#define NAMEENTER_H

#include <QDialog>

namespace Ui {
class NameEnter;
}

class NameEnter : public QDialog
{
    Q_OBJECT

    QString name;
    QString link;

public:
    explicit NameEnter(QWidget *parent = 0);
    ~NameEnter();

    QString getName();
    QString getLink();

private slots:
    void on_btnClose_clicked();
    void on_btnOK_clicked();

private:
    Ui::NameEnter *ui;
};

#endif // NAMEENTER_H
