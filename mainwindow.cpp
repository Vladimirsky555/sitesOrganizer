#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Органайзер сайтов");
    this->open = false;
    refresh();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::refresh()
{
    ui->lstMain->clear();

    for(int i = 0; i < s.getCount(); i++)
    {
        ui->lstMain->addItem(s.getItem(i)->getName());
        ui->lstMain->item(i)->setIcon(QIcon(":/images/list.png"));
    }
}


int MainWindow::defineCounts(QString filename)
{
    countLines = 0;
    fileIn.setFileName(filename);
    fileIn.open(QIODevice::ReadOnly);

    for(int i = 0; i < 10000; i++){
        QByteArray arr = fileIn.readLine();
        if(QString::fromUtf8(arr) != ""){
        countLines++;
        } else {
            break;
        }
    }

    return countLines + 1;
    fileIn.close();
}

void MainWindow::importFolders(QString filename)
{
    defineCounts(filename);

    fileIn.setFileName(filename);
    fileIn.open(QIODevice::ReadOnly);

    for(int i = 0; i < countLines; i++){

        QByteArray arr = fileIn.readLine();
        QRegExp rx("\">(.*)</H");

        int pos = 0;
        while((pos = rx.indexIn(QString::fromUtf8(arr), pos)) != -1){
            pos += rx.matchedLength();

            QString value = rx.cap(0).remove(0,2);
            value.chop(3);

            //Пишем категории в структуру (категория, указатель на модель)
            folder f;
            f.category = value;
            tmpList = new Listitem(value);
            f.li = tmpList;
            folders.append(f);

//            for(int j = 0; j < s.getCount(); j++){
//                if(s.getItem(j)->getName().contains(value)){
//                    return;
//                }
//            }


            s.addModel(tmpList);
        }
    }

//    s.saveToFile();
    fileIn.close();
    fileOut.close();
    refresh();

}

void MainWindow::importLinksinFolders(QString filename)
{
    QString value;
    QString import = "import";
    int pos;
    QString exept;

    fileIn.setFileName(filename);
    fileIn.open(QIODevice::ReadOnly);

    //Парсим названия сайтов и ссылки
    for(int i = 0; i < countLines; i++){
        QByteArray arr = fileIn.readLine();

        QRegExp rx1("\">[^</A>]+");
        QRegExp rx2("(http|https):\/\/[^\"]+");

        pos = 0;
        while((pos = rx1.indexIn(QString::fromUtf8(arr), pos)) != -1){
            pos += rx1.matchedLength();
            value = rx1.cap(0).remove(0,2);

            //Идём по тексту, пока не наткнёмся на категорию
            //Меняем темповую модель для записи ссылок
            for(int j = 0; j < folders.count(); j++){
                if(value == folders[j].category){
                    tmpList = folders[j].li;
                    exept = value;
                }
            }

            if(value != exept){
            tmpText = new TextItem(value, import);
            tmpList->addItem(tmpText);
            }

        }

        pos = 0;
        while((pos = rx2.indexIn(QString::fromUtf8(arr), pos)) != -1){
            pos += rx2.matchedLength();
            value = rx2.cap(0);
            tmpText->setLink(value);
        }

    }

//    s.saveToFile();
    fileIn.close();
    fileOut.close();
    refresh();
}

void MainWindow::importItems(QString filename)
{
    QString import = "import";
    QString value;
    int pos;
    defineCounts(filename);

    tmpList = new Listitem(import);

//    for(int j = 0; j < s.getCount(); j++){
//        if(s.getItem(j)->getName() == import){
//            return;
//        }
//    }

    s.insertItem(0,tmpList);

    if (filename == ""){
        QMessageBox b;
        b.setText("Выберите файл для поиска!");
        b.exec();
        return;
    }

    fileIn.setFileName(filename);
    fileIn.open(QIODevice::ReadOnly);

    //Парсим названия сайтов и ссылки
    for(int i = 0; i < countLines; i++){
        QByteArray arr = fileIn.readLine();

        QRegExp rx1("\">[^</A>]+");
        QRegExp rx2("(http|https):\/\/[^\"]+");

        pos = 0;
        while((pos = rx1.indexIn(QString::fromUtf8(arr), pos)) != -1){
            pos += rx1.matchedLength();
            value = rx1.cap(0).remove(0,2);
            tmpText = new TextItem(value, import);
            tmpList->addItem(tmpText);
        }

        pos = 0;
        while((pos = rx2.indexIn(QString::fromUtf8(arr), pos)) != -1){
            pos += rx2.matchedLength();
            value = rx2.cap(0);
            tmpText->setLink(value);
        }

    }

    tmpList->finalize();
//    s.saveToFile();
    fileIn.close();
    fileOut.close();
    refresh();
}




void MainWindow::textrefresh(Listitem *item)
{
    ui->lstMain->clear();

    for(int i = 0; i < s.getCount(); i++)
    {
        ui->lstMain->addItem(s.getItem(i)->getName());

        if(s.getItem(i) != item){
            ui->lstMain->item(i)->setIcon(QIcon(":/images/list.png"));
        } else {
            ui->lstMain->item(i)->setIcon(QIcon(":/images/edit.png"));
        }
    }
}

void MainWindow::closeAction()
{
    open = false;
    refresh();
}

void MainWindow::on_btnAdd_clicked()
{
   CategoryEnter ce;
   ce.exec();

   QString category = ce.getCategory();
   Listitem *item = new Listitem(category);

   if(ce.getCategory() != ""){
   s.addModel(item);
   } else {
       delete item;
       QMessageBox box;
       box.setText("Введите категорию!");
       box.exec();
       return;
   }

   refresh();
}


void MainWindow::on_btnInsert_clicked()
{
    CategoryEnter ce;
    ce.exec();

    QString category = ce.getCategory();
    Listitem *model = new Listitem(category);

    if(ce.getCategory() != ""){
    s.insertItem(currentIndex, model);
    } else {
        delete model;
        QMessageBox box;
        box.setText("Введите категорию!");
        box.exec();
        return;
    }

    refresh();
}

//void MainWindow::on_btnClear_clicked()
//{
//   s.allClear();
//   emit allClear();
//   refresh();
//}

void MainWindow::on_btnDelete_clicked()
{
    s.deleteItem(ui->lstMain->currentRow());
    emit allClear();
    refresh();
}

void MainWindow::on_lstMain_clicked(const QModelIndex &index)
{
    this->currentIndex = index.row();
}



void MainWindow::on_lstMain_doubleClicked(const QModelIndex &index)
{
    if(!open){
    current = s.getItem(index.row());

    ListWidget *ListWdg = new ListWidget(current, s.getList());

    connect(this, SIGNAL(allClear()),
            ListWdg, SLOT(allClear()));

    connect(ListWdg, SIGNAL(textChanged(Listitem*)),
            this, SLOT(textrefresh(Listitem*)));

    connect(ListWdg, SIGNAL(closeAction()),
            this, SLOT(closeAction()));



    ui->lstMain->item(index.row())->setIcon(QIcon(":/images/edit.png"));

    ListWdg->show();
    open = true;
    }
}



void MainWindow::closeEvent(QCloseEvent *event)
{
    emit allClear();
}

bool MainWindow::checkRegExp(QRegExp rx)
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



void MainWindow::on_down_triggered()
{
    s.replaceDownItem(currentIndex);
    refresh();
}

void MainWindow::on_up_triggered()
{
    s.replaceUpItem(currentIndex);
    refresh();
}

void MainWindow::on_actionSearch_triggered()
{
    SearchForm *sf = new SearchForm();
    sf->show();
}

void MainWindow::on_actionSave_triggered()
{
    s.saveToFile();
}




void MainWindow::on_actionFile_triggered()
{
    QFileDialog dialog;
    fileforimport = dialog.getOpenFileName();
}

void MainWindow::on_actionImport_triggered()
{
    importItems(fileforimport);
}



void MainWindow::on_actionImporttoFolders_triggered()
{
    importFolders(fileforimport);
    importLinksinFolders(fileforimport);
}
