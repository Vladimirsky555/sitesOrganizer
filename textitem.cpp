#include "textitem.h"
#include <QIODevice>
#include <QDataStream>
#include <QByteArray>


TextItem::TextItem(QString name, QString link, QObject *parent) : QObject(parent)
{
    this->name = name;
    this->link = link;
}

TextItem::TextItem(QByteArray arr)
{    
    QDataStream reader(&arr, QIODevice::ReadOnly);
    reader >> this->name >> this->link >> this->text;
}


QByteArray TextItem::saveIt()
{
    QByteArray arr;
    QDataStream writer(&arr, QIODevice::WriteOnly);

    writer << this->name << this->link << this->text;

    return arr;
}

QString TextItem::getName()
{
    return this->name;
}

void TextItem::setName(QString name)
{
    this->name = name;
}

QString TextItem::getLink()
{
    return this->link;
}

void TextItem::setLink(QString link)
{
    this->link = link;
}

QString TextItem::getText()
{
    return this->text;
}

void TextItem::setText(QString text)
{
    this->text = text;
}


