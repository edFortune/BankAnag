#ifndef WIDGETSTYLEHEADER_H
#define WIDGETSTYLEHEADER_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

QWidget *string_and_label_WidgetStyle(QString dataname, QLabel *lab_Data);
QWidget *string_and_label_ColorWidgetStyle(QString titre,QString col_titre,QLabel *dataLabel,QString col_data);
QWidget* stringHeader_and_label_ColorWidgetStyle(QString titre,QString col_titre,QLabel *dataLabel,QString col_data);
void ButtonRoundStyle(QPushButton*);


#endif // WIDGETSTYLEHEADER_H
