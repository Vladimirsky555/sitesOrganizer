#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QObject>

class TextItem : public QObject
{
    Q_OBJECT

    QString name;
    QString link;
    QString text;

public:
    explicit TextItem(QString name, QString link, QObject *parent = 0);
    TextItem(QByteArray arr);


    QString getName();
    void setName(QString name);

    QString getLink();
    void setLink(QString link);

    QString getText();
    void setText(QString text);

    QByteArray saveIt();

signals:

public slots:
};

#endif // TEXTITEM_H
