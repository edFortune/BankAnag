#include "dpushbutton.h"

DPushButton::DPushButton(QWidget *parent)
    :QPushButton(parent)
{

}

DPushButton::DPushButton(const QString &text)
    :QPushButton(text)
{
    setObjectName("DPushButton");
    setStyleSheet("#DPushButton{ background-color: #4CAF50;"
                  "border: none;"
                  "color: white;"
                  "padding: 10px 25px;"
                  "text-align: center;"
                  "text-decoration: none;"
                  "font-size: 12px;}"
                  "#DPushButton:hover{background-color:lightgray;}");

}

DPushButton::DPushButton(const QString &text, QWidget *parent)
    :QPushButton(text,parent)
{

}

void DPushButton::setCustomStyleSheet(const QString style)
{
    setStyleSheet(styleSheet()+style);
}


