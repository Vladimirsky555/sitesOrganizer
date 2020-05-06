#ifndef MOVETOCATEGORY_H
#define MOVETOCATEGORY_H

#include <QDialog>
#include "storage.h"
#include "listitem.h"
#include "textitem.h"
#include "listwidget.h"

namespace Ui {
class MovetoCategory;
}

class MovetoCategory : public QDialog
{
    Q_OBJECT

    Storage s;
    Listitem *li;
    TextItem *ti;
    QList<Listitem*> models;


public:
    explicit MovetoCategory(Listitem *li, TextItem *ti,QList<Listitem*>, QWidget *parent = 0);
    ~MovetoCategory();


private slots:
    void on_listWidget_clicked(const QModelIndex &index);

signals:
    void refresh();

private:
    Ui::MovetoCategory *ui;
};

#endif // MOVETOCATEGORY_H
