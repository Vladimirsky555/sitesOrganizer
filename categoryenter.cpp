#include "categoryenter.h"
#include "ui_categoryenter.h"

#include <QMessageBox>

CategoryEnter::CategoryEnter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CategoryEnter)
{
    ui->setupUi(this);
    setWindowTitle("Категория");
}

CategoryEnter::~CategoryEnter()
{
    delete ui;
}

QString CategoryEnter::getCategory()
{
    return this->category;
}

void CategoryEnter::on_btnOK_clicked()
{
   category = ui->edtCategory->text();

   if(category == ""){
       QMessageBox b;
       b.setText("Пустая строка!");
       b.exec();
       return;
   }

   close();

}
