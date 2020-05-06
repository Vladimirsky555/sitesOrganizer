#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "categoryenter.h"
#include "listitem.h"
#include "textitem.h"
#include "listwidget.h"
#include "textwidget.h"
#include "storage.h"
#include "searchform.h"
#include "qregexphighlighter.h"




namespace Ui {
class MainWindow;
}

struct folder{
    QString category;
    Listitem *li;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Storage s;
    Listitem *current;

    bool open;
    int currentIndex;

    QFile fileIn;
    QFile fileOut;
    QString fileforimport;
    int countLines;

    TextItem *tmpText;
    Listitem *tmpList;

    QList<folder> folders;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    refresh();
    void importFolders(QString);
    void importLinksinFolders(QString);
    void importItems(QString);
    int defineCounts(QString filename);

private slots:
    void textrefresh(Listitem*);
    void closeAction();
    void on_btnAdd_clicked();    
    void on_lstMain_doubleClicked(const QModelIndex &index);
    void on_btnDelete_clicked();
    void on_btnInsert_clicked();
    void on_lstMain_clicked(const QModelIndex &index);
    void on_down_triggered();
    void on_up_triggered();
    void on_actionSearch_triggered();
    void on_actionSave_triggered();
    void on_actionImport_triggered();
    void on_actionFile_triggered();
    void on_actionImporttoFolders_triggered();
//    void on_btnClear_clicked();


signals:
    void allClear();

protected:
   void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    bool checkRegExp(QRegExp rx);
};

#endif // MAINWINDOW_H
