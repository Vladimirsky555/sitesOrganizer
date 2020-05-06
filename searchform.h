#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>
#include <QRegExp>
#include <QMessageBox>

#include "storage.h"
#include "listitem.h"
#include "textitem.h"
#include "qregexphighlighter.h"

namespace Ui {
class SearchForm;
}

struct searchItem {
    QString category;
    QString name;
    QString text;
    QString link;
    int num;
};

class SearchForm : public QWidget
{
    Q_OBJECT

    Storage s;
    QRegexpHighlighter *highlighter;
    QList<searchItem> searchItems;
    QList<Listitem*> items;
    Listitem* current;
    TextItem* currentSub;

    QString currentText;
    bool flag;


public:
    explicit SearchForm(QWidget *parent = 0);
    ~SearchForm();

    void textFind();

private slots:
    void on_edtPattern_textChanged(const QString &arg1);
    void on_edtPattern_returnPressed();
    void on_lstResults_clicked(const QModelIndex &index);
    void on_lstResults_doubleClicked(const QModelIndex &index);

private:
    Ui::SearchForm *ui;
    bool checkRegExp(QRegExp rx);
};

#endif // SEARCHFORM_H
