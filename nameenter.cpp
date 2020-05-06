#include "nameenter.h"
#include "ui_nameenter.h"

#include <QMessageBox>

NameEnter::NameEnter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameEnter)
{
    ui->setupUi(this);
    setWindowTitle("Название сайта и ссылка");
}

NameEnter::~NameEnter()
{
    delete ui;
}

QString NameEnter::getName()
{
    return this->name;
}

QString NameEnter::getLink()
{
    return this->link;
}

void NameEnter::on_btnClose_clicked()
{
    close();
}

void NameEnter::on_btnOK_clicked()
{
    this->name = ui->edtName->text();
    this->link = ui->edtLink->text();

    if(name == "" || link == ""){
        QMessageBox b;
        b.setText("Пустая строка!");
        b.exec();
        return;
    }

    close();
}
