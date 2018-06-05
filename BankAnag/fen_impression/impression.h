#ifndef IMPRESSION_H
#define IMPRESSION_H

#include <QObject>
#include <QPrinter>

class Impression : public QObject
{
    Q_OBJECT
public:
    explicit Impression(QObject *parent = 0);
    
signals:
    
public slots:

private:
    QPrinter printer;

};

#endif // IMPRESSION_H
