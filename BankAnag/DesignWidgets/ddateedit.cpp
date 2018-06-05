#include "ddateedit.h"

DDateEdit::DDateEdit(QWidget *parent) : QWidget(parent)
{


}

DDateEdit::DDateEdit(QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setMargin(0);
    this->setLayout(vbox);

    dateEdt_tag = new QLabel(tag);
    dateEdt_tag->setStyleSheet("background-color:lightgray;color:gray;");
    dateEdt_tag->setMargin(5);
    dateEdt_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    dateEdt_tag->setMaximumHeight(100);
    vbox->addWidget(dateEdt_tag);

    dateEdit = new QDateEdit;
    vbox->addWidget(dateEdit);

    this->setMaximumHeight(50);
}

void DDateEdit::setCalendarPopup(bool enable)
{
    dateEdit->setCalendarPopup(enable);
}

QDate DDateEdit::date()
{
    return dateEdit->date();
}

void DDateEdit::setCurrentDate()
{
    dateEdit->setDate(QDate::currentDate());
}

void DDateEdit::setDate(const QDate &date)
{
    dateEdit->setDate(date);
}
