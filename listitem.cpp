#include "listitem.h"
#include <QIODevice>
#include <QDataStream>
#include <QByteArray>
#include <QDebug>


Listitem::Listitem(QString name, QObject *parent) : QObject(parent)
{
    this->name = name;
}

Listitem::Listitem(QByteArray arr)
{
    QDataStream reader(&arr, QIODevice::ReadOnly);

    reader >> this->name;

    while(!reader.atEnd()){
        QByteArray tmp;
        reader >> tmp;
       items.append(new TextItem(tmp));
    }
}




QByteArray Listitem::saveIt()
{
    QByteArray arr;
    QDataStream writer(&arr, QIODevice::WriteOnly);

    writer << this->name;

    for(int i = 0; i < items.size(); i++){
        writer << this->items[i]->saveIt();
    }

    return arr;
}

void Listitem::finalize()
{
    for(int i = 0; i < items.size(); i++){
        if(items[i]->getLink() == "import"){
            items.removeAt(i);
        }
    }
}

QString Listitem::getName()
{
    return this->name;
}

void Listitem::setName(QString name)
{
    this->name = name;
}

void Listitem::addItem(TextItem *ti)
{
    items.append(ti);
}

void Listitem::deleteItem(int id)
{
    items.removeAt(id);
}

void Listitem::deleteItem2(TextItem *ti)
{
    items.removeAll(ti);
}



void Listitem::delItem(TextItem *ti)
{
    delete ti;
}

TextItem *Listitem::getTextItem(int id)
{
    return items[id];
}

int Listitem::getCount()
{
    return items.count();
}

void Listitem::allClear()
{
    items.clear();
}

void Listitem::insertItem(int id, TextItem *item)
{
    if (items.contains(item)) return;

    if(items.count() == 0){
        items.append(item);
        return;
    }

    this->items.insert(id+1, item);
    return;
}

void Listitem::replaceDownItem(int id)
{
    TextItem *temp = items[id];

    if(id < items.count() - 1){
        items[id] = items[id+1];
        items[id+1] = temp;
    }
}

void Listitem::replaceUpItem(int id)
{
    TextItem *temp = items[id];

    if(id > 0){
        items[id] = items[id-1];
        items[id-1] = temp;
    }
}


