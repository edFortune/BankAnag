#include "dlabel.h"

DLabel::DLabel(QWidget *parent) : QWidget(parent)
{

}

DLabel::DLabel(const QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setMargin(0);
    this->setLayout(vbox);

    label_tag = new QLabel(tag);
    label_tag->setStyleSheet("background-color:lightgray;color:gray;");
    label_tag->setMargin(5);
    label_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    label_tag->setMaximumHeight(100);
    vbox->addWidget(label_tag);

    label = new QLabel("---");
    label->setMargin(5);
    label->setAlignment(Qt::AlignLeft);
    vbox->addWidget(label);

    this->setMaximumHeight(50);

}

DLabel::DLabel(const QString tag, const int alignmentLabel)
{
    switch (alignmentLabel) {
    case 200:
        setConstructorAlignLabelTop(tag);
        break;
    case 400:
        setConstructorAlignLabelLeft(tag);
        break;
    default:
        break;
    }

}

void DLabel::setConstructorAlignLabelTop(const QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setMargin(0);
    this->setLayout(vbox);

    label_tag = new QLabel(tag);
    label_tag->setStyleSheet("background-color:lightgray;color:gray;");
    label_tag->setMargin(5);
    label_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    label_tag->setMaximumHeight(100);
    vbox->addWidget(label_tag);

    label = new QLabel("---");
    label->setMargin(5);
    label->setAlignment(Qt::AlignLeft);
    vbox->addWidget(label);

    this->setMaximumHeight(50);
}

void DLabel::setConstructorAlignLabelLeft(const QString tag)
{
    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setSpacing(2);
    hbox->setMargin(0);
    this->setLayout(hbox);

    label_tag = new QLabel(tag);
    label_tag->setStyleSheet("background-color:lightgray;color:gray;");
    label_tag->setMargin(5);
    label_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    label_tag->setMaximumWidth(100);
    hbox->addWidget(label_tag);

    label = new QLabel("---");
    label->setMargin(5);
    label->setAlignment(Qt::AlignLeft);
    hbox->addWidget(label);

    this->setMaximumHeight(30);
}

void DLabel::setText(const QString &text)
{
    label->setText(text);
}

QString DLabel::text() const
{
    return label->text();
}

void DLabel::setColor(const QString &color)
{
    label->setStyleSheet("color:"+color+";");
}

void DLabel::setBold(bool)
{
    label->setFont(QFont("",10,QFont::Bold,false));
}

void DLabel::setTextFromInt(int i)
{
    label->setText(QLocale(QLocale::English).toString(i));
}

void DLabel::setTextFromDouble(double d)
{
    label->setText(QLocale(QLocale::English).toString(d));
}

void DLabel::setPriceTextFromDouble(QString currency, double amount)
{
    label->setText(currency+" "+ QLocale(QLocale::English).toString(amount));
}

void DLabel::setTextFromDoubleToInt(double d)
{
    label->setText(QLocale(QLocale::English).toString((int)d));
}


