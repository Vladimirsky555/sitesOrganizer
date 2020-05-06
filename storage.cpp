#include "storage.h"
#include <QFile>
#include <QByteArray>


#define FILENAME "data"

Storage::Storage(QObject *parent) : QObject(parent)
{
    QFile f(FILENAME);
    if (!f.exists()) return;

    f.open(QFile::ReadOnly);
    QByteArray data = f.readAll();
    f.close();

    QDataStream str(data);    

    while (!str.atEnd()) {
        QByteArray arr;
        str >> arr;

        Listitem *item = new Listitem(arr);
        addModel(item);
    }
}



Storage::~Storage() {

    QFile f(FILENAME);
    f.open(QFile::WriteOnly|QFile::Truncate);

    QDataStream str(&f);

    for (int i = 0; i < models.count(); i++)
        str << models[i]->saveIt();

    f.close();
}

QList<Listitem *> Storage::getList()
{
    return this->models;
}

QStringList Storage::getCategoryList()
{
    QStringList tmp;
    for(int i = 0; i < models.count(); i++){
        tmp[i] = models[i]->getName();
    }
    return tmp;
}

void Storage::addModel(Listitem *item)
{

    if(models.contains(item))return;
    models.append(item);

}

void Storage::deleteItem(int id)
{
    models.removeAt(id);
}

Listitem *Storage::getItem(int id)
{
    return models[id];
}

void Storage::allClear()
{

    for(int i = 0; i < models.count(); i++){
        models.at(i)->allClear();
    }

    models.clear();
}

int Storage::getCount()
{
    return models.count();
}

int Storage::getID(Listitem *item)
{
    for(int i = 0; i < models.count(); i++)
    {
        if(item == models.at(i)){
            return i;
        }
    }
}

void Storage::insertItem(int index, Listitem *model)
{
    if (models.contains(model)) return;

    if(models.count() == 0){
        models.append(model);
        return;
    }

    this->models.insert(index+1, model);
    return;
}

void Storage::replaceDownItem(int id)
{
    Listitem *temp = models[id];

    if(id < models.count() - 1){
        models[id] = models[id+1];
        models[id+1] = temp;
    }
}

void Storage::replaceUpItem(int id)
{
    Listitem *temp = models[id];

    if(id > 0){
        models[id] = models[id-1];
        models[id-1] = temp;
    }
}

void Storage::saveToFile()
{
    QFile f(FILENAME);
    f.open(QFile::WriteOnly|QFile::Truncate);

    QDataStream str(&f);

    for (int i = 0; i < models.count(); i++)
        str << models[i]->saveIt();

    f.close();
}


