#ifndef STORAGE_H
#define STORAGE_H

#include <QObject>
#include <QIODevice>
#include <QDataStream>

#include "listitem.h"

class Storage : public QObject
{
    Q_OBJECT

    QList<Listitem*> models;

public:
    explicit Storage(QObject *parent = 0);
    ~Storage();

    QList<Listitem*> getList();
    QStringList getCategoryList();
    void addModel(Listitem* item);
    void deleteItem(int id);
    Listitem* getItem(int id);
    void allClear();
    int getCount();
    int getID(Listitem* item);
    void insertItem(int, Listitem*);
    void replaceDownItem(int);
    void replaceUpItem(int);
    void saveToFile();

signals:

public slots:
};

#endif // STORAGE_H
