#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>

#include "textitem.h"

namespace Ui {
class TextWidget;
}

class TextWidget : public QWidget
{
    Q_OBJECT

    TextItem *ti;

public:
    explicit TextWidget(TextItem *ti, QWidget *parent = 0);
    ~TextWidget();

private slots:
    void allClear();
    void on_bntOK_clicked();

    void on_edtName_textChanged(const QString &arg1);

signals:
    closeTextAction();
    textChanged(TextItem*);

protected:
   void closeEvent(QCloseEvent *event);

private:
    Ui::TextWidget *ui;
};

#endif // TEXTWIDGET_H
