#ifndef DGROUPBOX_H
#define DGROUPBOX_H

#include <QWidget>
#include <QLabel>

#include <QVBoxLayout>
#include <QGridLayout>
#include <QLayout>


class DGroupBox : public QWidget
{
    Q_OBJECT
public:
    explicit DGroupBox(QWidget *parent = 0);
    DGroupBox(QString tag);

    void setBodyLayout(QLayout*);
    void setHeaderBgColor(QString bgColor);

signals:

public slots:


private:
    QLabel *groupBox_header;
    QWidget *groupBox_body;
};

#endif // DGROUPBOX_H
