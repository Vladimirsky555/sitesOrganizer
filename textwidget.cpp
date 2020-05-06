#include "textwidget.h"
#include "ui_textwidget.h"

TextWidget::TextWidget(TextItem *ti, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextWidget)
{
    ui->setupUi(this);
    this->ti = ti;

    ui->edtName->setText(this->ti->getName());
    ui->edtLink->setText(this->ti->getLink());
    ui->edtText->setText(this->ti->getText());

    setWindowTitle(this->ti->getName());
}

TextWidget::~TextWidget()
{
    delete ui;
}

void TextWidget::on_edtName_textChanged(const QString &arg1)
{
    ti->setName(arg1);
    emit textChanged(ti);
}

void TextWidget::allClear()
{
    close();
}

void TextWidget::on_bntOK_clicked()
{
    ti->setText(ui->edtText->toHtml());
    ti->setLink(ui->edtLink->text());
    emit closeTextAction();
    close();
}

void TextWidget::closeEvent(QCloseEvent *event)
{
    emit closeTextAction();
}




