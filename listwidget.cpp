#include "listwidget.h"
#include "ui_listwidget.h"

#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>



ListWidget::ListWidget(Listitem* li,QList<Listitem*> models,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    this->li = li;
    this->models = models;
    this->open = false;

    ui->btnEdit->setEnabled(false);
    ui->btnDelete->setEnabled(false);
    ui->btnDown->setEnabled(false);
    ui->btnUp->setEnabled(false);
    ui->btnMove->setEnabled(false);

    setWindowTitle(this->li->getName());
    ui->edtName->setText(li->getName());
    ui->lstList->clear();
    refresh();
}






ListWidget::~ListWidget()
{
    delete ui;
}

ListWidget::refresh()
{
    ui->lstList->clear();
    for(int i = 0; i < li->getCount(); i++){
        ui->lstList->addItem(li->getTextItem(i)->getName());
        ui->lstList->item(i)->setIcon(QIcon(":/images/icons8-website-80.png"));
    }
}



void ListWidget::closeTextAction()
{
    ui->btnEdit->setEnabled(false);
    ui->btnDelete->setEnabled(false);

    open = false;
    refresh();
}

ListWidget::textrefresh(TextItem *item)
{
    ui->lstList->clear();

    for(int i = 0; i < li->getCount(); i++)
    {
       ui->lstList->addItem(li->getTextItem(i)->getName());

        if(li->getTextItem(i) != item){
            ui->lstList->item(i)->setIcon(QIcon(":/images/icons8-website-80.png"));
        } else {
            ui->lstList->item(i)->setIcon(QIcon(":/images/edit.png"));
        }
    }
}

void ListWidget::refreshfromsingal()
{
    ui->lstList->clear();

    for(int i = 0; i < li->getCount(); i++)
    {
        ui->lstList->addItem(li->getTextItem(i)->getName());
        ui->lstList->item(i)->setIcon(QIcon(":/images/icons8-website-80.png"));

    }
}





void ListWidget::allClear()
{
    close();
    emit allTextWidgetsClear();
}

void ListWidget::on_btnAdd_clicked()
{
    NameEnter ne;
    ne.exec();

    QString name = ne.getName();
    QString link = ne.getLink();

    TextItem *ti = new TextItem(name, link);

    if(ne.getName() != "" || ne.getLink() != ""){
        if(ne.getLink().contains("http://") || ne.getLink().contains("https://")){
            li->addItem(ti);
        } else {
            delete ti;
            QMessageBox box;
            box.setText("Введите название сайта и ссылку! Ссылка начинается с "
                        "http:// или https://");
            box.exec();
            return;
        }
    }

    refresh();
}





void ListWidget::on_btnDelete_clicked()
{
    li->deleteItem(ui->lstList->currentRow());
    emit allTextWidgetsClear();
    refresh();
}

//void ListWidget::on_btnClear_clicked()
//{
//   li->allClear();
//   emit allTextWidgetsClear();
//   refresh();
//}

void ListWidget::on_lstList_clicked(const QModelIndex &index)
{
    ui->btnEdit->setEnabled(true);
    ui->btnDelete->setEnabled(true);
    ui->btnDown->setEnabled(true);
    ui->btnUp->setEnabled(true);
    ui->btnMove->setEnabled(true);
    this->currentIndex = ui->lstList->currentRow();
    currentTextItem = li->getTextItem(index.row());
}

void ListWidget::on_lstList_doubleClicked(const QModelIndex &index)
{
    currentTextItem = li->getTextItem(index.row());
    if (currentTextItem->getLink() == "") return;
    else {
        QDesktopServices::openUrl(QUrl(currentTextItem->getLink()));
    }
}




void ListWidget::on_btnEdit_clicked()
{
    if(!open){
    currentTextItem = li->getTextItem(ui->lstList->currentRow());
    ui->lstList->item(ui->lstList->currentRow())->setIcon(QIcon(":/images/edit.png"));
    TextWidget *TxtWdg = new TextWidget(currentTextItem);

    connect(this, SIGNAL(allTextWidgetsClear()),
            TxtWdg, SLOT(allClear()));

    connect(TxtWdg, SIGNAL(closeTextAction()),
            this, SLOT(closeTextAction()));

    connect(TxtWdg, SIGNAL(textChanged(TextItem*)),
            this, SLOT(textrefresh(TextItem*)));

    TxtWdg->show();
    open = true;
    }
}



void ListWidget::on_edtName_textChanged(const QString &arg1)
{
    li->setName(arg1);
    emit textChanged(li);
}

void ListWidget::closeEvent(QCloseEvent *event)
{   
    emit allTextWidgetsClear();
    emit closeAction();
}


void ListWidget::on_btnInsert_clicked()
{
    NameEnter ne;
    ne.exec();

    QString name = ne.getName();
    QString link = ne.getLink();

    TextItem *ti = new TextItem(name, link);

    if(ne.getName() != "" || ne.getLink() != ""){
        if(ne.getLink().contains("http://") || ne.getLink().contains("https://")){
            li->insertItem(currentIndex, ti);
        } else {
            delete ti;
            QMessageBox box;
            box.setText("Введите название сайта и ссылку! Ссылка начинается с "
                        "http:// или https://");
            box.exec();
            return;
        }
    }

    refresh();
}

void ListWidget::on_btnUp_clicked()
{
    li->replaceUpItem(currentIndex);
    refresh();
}

void ListWidget::on_btnDown_clicked()
{
    li->replaceDownItem(currentIndex);
    refresh();
}

void ListWidget::on_btnMove_clicked()
{
    MovetoCategory *move = new MovetoCategory(li, currentTextItem, models);

    connect(move, SIGNAL(refresh()),
            this, SLOT(refreshfromsingal()));

    move->exec();
}
