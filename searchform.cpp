#include "searchform.h"
#include "ui_searchform.h"

#include <QDesktopServices>
#include <QUrl>

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);

    setWindowTitle("Поисковик");

    highlighter = new QRegexpHighlighter(this);
    highlighter->setDocument(ui->edtText->document());
    highlighter->setPattern(ui->edtPattern->text());
}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::textFind()
{
    searchItems.clear();
    ui->edtText->clear();
    ui->edtText->append("Режим исследования текстов!");
    ui->edtText->append("");
    ui->edtText->append("В квадратных скобках - число, "
                        "указывающее на то, сколько раз в тексте "
                        "встретились слово или фраза.");

    int c = 0;// количество повторений
    int n = 0;

        for(int i = 0; i < s.getCount(); i++){
            current = s.getItem(i);

            int cnt = 0;

            for(int j = 0; j < current->getCount(); j++){
                currentSub = current->getTextItem(j);

                //Реализация поиска по описаниям или названиям
                if(flag){
                    currentText = currentSub->getText();
                } else {
                    currentText = currentSub->getName();
                }


                QRegExp rx(ui->edtPattern->text());
                if(!checkRegExp(rx))return;
                int pos = 0;
                while((pos = rx.indexIn(currentText, pos)) != -1){
                    pos += rx.matchedLength();
                    cnt++;
                    c++;
                }           


                if(cnt != 0){
                searchItem si;
                si.category = current->getName();
                si.name = currentSub->getName();//название сайта
                si.text = currentSub->getText();// Описание сайта
                si.link = currentSub->getLink();
                si.num = cnt;
                searchItems.append(si);
                }

                cnt = 0;
            }            
        }

        //Cортировка
                for(int i = 0; i < searchItems.count(); i++)
                {
                    for(int j = 0; j < searchItems.count() - 1; j++)
                    {
                        if(searchItems[j].num < searchItems[j + 1].num)
                        {
                            searchItem tmp = searchItems[j];
                            searchItems[j] = searchItems[j + 1];
                            searchItems[j + 1] = tmp;
                        }
                    }
                }

        //Вывод результата на экран
        ui->lstResults->clear();
        for(int i = 0; i < searchItems.size(); i++){
            n++;

            ui->lstResults->addItem(searchItems[i].category + ", [" +
                                    QString::number(searchItems[i].num) +
                                    "] " + searchItems[i].name);
            ui->lstResults->item(i)->setIcon(QIcon(":/images/search.png"));
        }



        //Завершающая информация
        ui->lstResults->addItem(" ");
        ui->lstResults->addItem("Итого: " + QString::number(c) + " повторений" + " в " + QString::number(n) + " текстах");
        ui->lstResults->addItem("Поиск завершен!");
        ui->edtText->append(" ");
        ui->edtText->append(" ");
        ui->edtText->append(QString::number(c) + " повторений" + " в " + QString::number(n) + " текстах");
        ui->edtText->append("Поиск завершен!");
        }    





bool SearchForm::checkRegExp(QRegExp rx)
{
    if(rx.isValid() && !rx.isEmpty() && !rx.exactMatch("")){
        return true;
    }else{
        QMessageBox::information(this,
                                 "Информсообщение",
                                 trUtf8("Некорректный шаблон регулярного выражения!"));
        return false;
    }
}

void SearchForm::on_edtPattern_textChanged(const QString &str)
{
    highlighter->setPattern(str);
    highlighter->rehighlight();
}

void SearchForm::on_edtPattern_returnPressed()
{
    //Для поиска по описаниям или по названиям
    if(ui->checkBox->isChecked()){
        flag = true;
    } else {
        flag = false;
    }

    textFind();
}

void SearchForm::on_lstResults_clicked(const QModelIndex &index)
{
    if(index.row() >= searchItems.size()){
        QMessageBox box;
        box.setText("Спасибо!");
        box.exec();
        return;
    }

    //Выбрасываем текст, который нашли, по клику
    QString text = searchItems[index.row()].text;
    ui->edtText->setText(text);
}

void SearchForm::on_lstResults_doubleClicked(const QModelIndex &index)
{
    //Переходим на сайт по клику
    QString link = searchItems[index.row()].link;
    if (link == "") return;
    else {
        QDesktopServices::openUrl(QUrl(link));
    }
}
