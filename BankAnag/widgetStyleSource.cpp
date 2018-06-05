#include "widgetStyleHeader.h"


//1) string and label widget style in QHboxLayout
QWidget* string_and_label_WidgetStyle(QString dataname,QLabel *lab_Data)
{
    QWidget *wid = new QWidget;

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setSpacing(0);
    hlayout->setMargin(1);
    wid->setLayout(hlayout);

    QLabel *lab_dataName = new QLabel(dataname);
    lab_dataName->setFont(QFont("",10,QFont::Bold,false));
    lab_dataName->setMargin(5);
    lab_dataName->setMaximumHeight(40);
    lab_dataName->setStyleSheet("background-color:gray;color:white");
    hlayout->addWidget(lab_dataName);

    QLabel *lab_dataInfo = lab_Data;
    lab_dataInfo->setFont(QFont("",10,10,false));
    lab_dataInfo->setMargin(5);
    lab_dataInfo->setMaximumHeight(40);
    lab_dataInfo->setStyleSheet("background-color:#CD3333;color:white");
    hlayout->addWidget(lab_dataInfo);

    return wid;

}

//1.1) string and label with color widget style in QHboxLayout
QWidget* string_and_label_ColorWidgetStyle(QString titre, QString col_titre, QLabel *dataLabel, QString col_data)
{
    QWidget *wid = new QWidget;

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->setSpacing(0);
    hlayout->setMargin(5);
    wid->setLayout(hlayout);

    QLabel *lab_dataName = new QLabel(titre);
    lab_dataName->setFont(QFont("",10,QFont::Bold,false));
    lab_dataName->setMargin(5);
    lab_dataName->setStyleSheet("background-color:"+col_titre+";color:white");
    hlayout->addWidget(lab_dataName,5);

    QLabel *lab_dataInfo = dataLabel;
    lab_dataInfo->setFont(QFont("",20,20,false));
    lab_dataInfo->setMargin(5);
    lab_dataInfo->setStyleSheet("background-color:"+col_data+";color:white");
    hlayout->addWidget(lab_dataInfo,5);

    return wid;
}


//2) Label widget and label with color widget style in QHboxLayout
QWidget* stringHeader_and_label_ColorWidgetStyle(QString titre,QString col_titre,QLabel *dataLabel,QString col_data)
{
    QWidget *wid = new QWidget;

    QVBoxLayout *v = new QVBoxLayout;
    v->setSpacing(0);
    wid->setLayout(v);


    QLabel *lab_titre = new QLabel(titre);
    lab_titre->setStyleSheet("background-color:"+col_titre+";color:white;");
    lab_titre->setFont(QFont("",10,QFont::Bold,false));
    lab_titre->setMargin(5);
    lab_titre->setMaximumHeight(30);
    v->addWidget(lab_titre);

    QLabel *lab_data = dataLabel;
    lab_data->setStyleSheet("background-color:"+col_data+";color:white;");
    lab_data->setAlignment(Qt::AlignCenter);
    lab_data->setFont(QFont("",20,20,false));
    lab_data->setMargin(5);
    v->addWidget(lab_data);

    return wid;
}


//3) button round style
void ButtonRoundStyle(QPushButton *button)
{
    QPushButton *bouton = button;
    bouton->setStyleSheet("QPushButton{color:white;"
                                      "border-radius: 5px;"
                                      "padding: 5px;"
                                      "background: qradialgradient(cx: 0.3, cy: -0.4,"
                                      "fx: 0.3, fy: -0.4,"
                                      "radius: 1.35, stop: 0 #fff, stop: 1 #888);"
                                      "min-width: 80px;}");

}

