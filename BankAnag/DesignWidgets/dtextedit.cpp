#include "dtextedit.h"

DTextEdit::DTextEdit(QWidget *parent) : QWidget(parent)
{


}

DTextEdit::DTextEdit(QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(0);
    vbox->setMargin(0);
    this->setLayout(vbox);

    textEdit_tag = new QLabel(tag);
    textEdit_tag->setStyleSheet("background-color:lightgray;color:gray;");
    textEdit_tag->setMargin(5);
    textEdit_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    textEdit_tag->setMaximumHeight(100);
    vbox->addWidget(textEdit_tag);

    messageError_tag = new QLabel("");
    messageError_tag->setStyleSheet("color:red;");
    messageError_tag->setMargin(5);
    messageError_tag->setHidden(true);
    vbox->addWidget(messageError_tag);

    textEdit = new QTextEdit;
    vbox->addWidget(textEdit);
}

QString DTextEdit::toPlainText()
{
    return textEdit->toPlainText();
}

void DTextEdit::clear()
{
    textEdit->clear();
}

void DTextEdit::setMessageError(QString msg)
{
    messageError_tag->setText(msg);
    messageError_tag->setHidden(false);
}

void DTextEdit::setHiddenMessageError(bool hidden)
{
    messageError_tag->setHidden(hidden);
}
