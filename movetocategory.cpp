#include "movetocategory.h"
#include "ui_movetocategory.h"


MovetoCategory::MovetoCategory(Listitem *li, TextItem *ti,QList<Listitem*> models,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovetoCategory)
{
    ui->setupUi(this);
    setWindowTitle("Выбор категории для перемещения");
    this->li = li;
    this->ti = ti;
    this->models = models;
    for(int i = 0; i < models.count(); i++){
        ui->listWidget->addItem(this->models[i]->getName());
        ui->listWidget->item(i)->setIcon(QIcon(":/images/list.png"));
    }
}

MovetoCategory::~MovetoCategory()
{
    delete ui;
}

void MovetoCategory::on_listWidget_clicked(const QModelIndex &index)
{
    QString category = ui->listWidget->item(index.row())->text();
    for(int i = 0; i < models.count(); i++){
        if(category == models[i]->getName()){
            TextItem *next = new TextItem(ti->getName(), ti->getLink());
            models[i]->addItem(next);
            li->deleteItem2(ti);
//            delete ti;
            emit refresh();
            close();
        }
    }
}
