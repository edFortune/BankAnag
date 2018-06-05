#include "dlineedit.h"

DLineEdit::DLineEdit(QWidget *parent):
    QWidget(parent)
{

}

DLineEdit::DLineEdit(QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setMargin(0);
    this->setLayout(vbox);

    lineEdit_tag = new QLabel(tag);
    lineEdit_tag->setStyleSheet("background-color:lightgray;color:gray;");
    lineEdit_tag->setMargin(5);
    lineEdit_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    lineEdit_tag->setMaximumHeight(100);
    vbox->addWidget(lineEdit_tag);

    lineEdit = new QLineEdit;
    vbox->addWidget(lineEdit);

    this->setMaximumHeight(50);

}

QString DLineEdit::text()
{
    return lineEdit->text();
}

void DLineEdit::clear()
{
    lineEdit->clear();
}

void DLineEdit::setCompleter(QCompleter *completer)
{
    lineEdit->setCompleter(completer);
}

void DLineEdit::setText(const QString &text)
{
    lineEdit->setText(text);
}

QString DLineEdit::text() const
{
    return lineEdit->text();
}


QLineEdit *DLineEdit::getLineEdit() const
{
    return lineEdit;
}
