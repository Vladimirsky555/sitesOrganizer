#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "textwidget.h"
#include "listitem.h"
#include "textitem.h"
#include "nameenter.h"
#include "movetocategory.h"


namespace Ui {
class ListWidget;
}

class ListWidget : public QWidget
{
    Q_OBJECT

    Listitem* li;
    TextItem* currentTextItem;
    int currentIndex;
    bool open;
    QStringList CatList;
    QList<Listitem*> models;



public:
    explicit ListWidget(Listitem* li,QList<Listitem*>,QWidget *parent = 0);
    ~ListWidget();

    refresh();



private slots:
    void closeTextAction();
    textrefresh(TextItem*);
    void refreshfromsingal();

    void allClear();
    void on_btnAdd_clicked();
    void on_btnDelete_clicked();
    void on_lstList_doubleClicked(const QModelIndex &index);
    void on_edtName_textChanged(const QString &arg1);
    void on_btnEdit_clicked();
    void on_lstList_clicked(const QModelIndex &index);
    void on_btnInsert_clicked();
    void on_btnUp_clicked();
    void on_btnDown_clicked();
    void on_btnMove_clicked();
//    void on_btnClear_clicked();


signals:
    allTextWidgetsClear();
    textChanged(Listitem*);
    closeAction();

 protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::ListWidget *ui;
};

#endif // LISTWIDGET_H
