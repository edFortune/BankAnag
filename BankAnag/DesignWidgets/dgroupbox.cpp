#include "dgroupbox.h"

DGroupBox::DGroupBox(QWidget *parent)
    : QWidget(parent)
{

}

DGroupBox::DGroupBox(QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(0);
    vbox->setMargin(0);
    this->setLayout(vbox);

    groupBox_header = new QLabel(tag);
    groupBox_header->setStyleSheet("background-color:lightgray;color:gray;");
    groupBox_header->setMargin(5);
    groupBox_header->setFont(QFont("Datus",8,QFont::Bold,false));
    groupBox_header->setMaximumHeight(35);
    vbox->addWidget(groupBox_header);

    groupBox_body = new QWidget(this);
    groupBox_body->setObjectName("groupBox_body");
    groupBox_body->setStyleSheet("#groupBox_body{background-color:white;border: 1px solid lightgray;}");
    vbox->addWidget(groupBox_body);

}

void DGroupBox::setBodyLayout(QLayout *l)
{
    groupBox_body->setLayout(l);
}

void DGroupBox::setHeaderBgColor(QString bgColor)
{
    groupBox_header->setStyleSheet("background-color:"+bgColor+";");
}

