#include "ddoublespinbox.h"

DDoubleSpinBox::DDoubleSpinBox(QWidget *parent) : QWidget(parent)
{

}

DDoubleSpinBox::DDoubleSpinBox(const QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setMargin(0);
    this->setLayout(vbox);

    doubleSpinBox_tag = new QLabel(tag);
    doubleSpinBox_tag->setStyleSheet("background-color:lightgray;color:gray;");
    doubleSpinBox_tag->setMargin(5);
    doubleSpinBox_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    doubleSpinBox_tag->setMaximumHeight(100);
    vbox->addWidget(doubleSpinBox_tag);

    messageError_tag = new QLabel("");
    messageError_tag->setStyleSheet("color:red;");
    messageError_tag->setHidden(true);
    vbox->addWidget(messageError_tag);

    doubleSpinBox = new QDoubleSpinBox;
    vbox->addWidget(doubleSpinBox);

    this->setMaximumHeight(50);

}

void DDoubleSpinBox::setMessageError(QString msg)
{
    messageError_tag->setText(msg);
    messageError_tag->setHidden(false);
}

void DDoubleSpinBox::setHiddenMessageError(bool hidden)
{
    messageError_tag->setHidden(hidden);
}

double DDoubleSpinBox::value()
{
    return doubleSpinBox->value();
}

void DDoubleSpinBox::setValue(double val)
{
    doubleSpinBox->setValue(val);
}

void DDoubleSpinBox::setMinimum(double min)
{
    doubleSpinBox->setMinimum(min);
}

void DDoubleSpinBox::setMaximum(double max)
{
    doubleSpinBox->setMaximum(max);
}

QDoubleSpinBox *DDoubleSpinBox::getDoubleSpinBox() const
{
    return doubleSpinBox;
}
