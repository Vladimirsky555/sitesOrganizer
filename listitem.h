#ifndef LISTITEM_H
#define LISTITEM_H

#include <QObject>
#include "textitem.h"

class Listitem : public QObject
{
    Q_OBJECT

    QString name;
    QList<TextItem*> items;


public:
    explicit Listitem(QString name, QObject *parent = 0);
    Listitem(QByteArray arr);

    QString getName();
    void setName(QString name);

    void addItem(TextItem* ti);
    void deleteItem(int);
    void deleteItem2(TextItem* ti);
    void delItem(TextItem *ti);
    TextItem* getTextItem(int id);
    int getCount();
    void allClear();
    void insertItem(int, TextItem*);
    void replaceDownItem(int);
    void replaceUpItem(int);

    QByteArray saveIt();

    void finalize();


signals:

public slots:
};

#endif // LISTITEM_H
