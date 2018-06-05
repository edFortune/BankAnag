#include "dspinbox.h"

DSpinBox::DSpinBox(QWidget *parent) : QWidget(parent)
{

}

DSpinBox::DSpinBox(const QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setMargin(0);
    this->setLayout(vbox);

    spinBox_tag = new QLabel(tag);
    spinBox_tag->setStyleSheet("background-color:lightgray;color:gray;");
    spinBox_tag->setMargin(5);
    spinBox_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    spinBox_tag->setMaximumHeight(100);
    vbox->addWidget(spinBox_tag);

    spinBox = new QSpinBox;
    vbox->addWidget(spinBox);

    this->setMaximumHeight(50);

}

int DSpinBox::value()
{
    return spinBox->value();
}
