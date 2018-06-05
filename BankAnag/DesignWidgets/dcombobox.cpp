#include "dcombobox.h"

DComboBox::DComboBox(QWidget *parent) : QWidget(parent)
{

}

DComboBox::DComboBox(QString tag)
{
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->setSpacing(2);
    vbox->setMargin(0);
    this->setLayout(vbox);

    comboBox_tag = new QLabel(tag);
    comboBox_tag->setStyleSheet("background-color:lightgray;color:gray;");
    comboBox_tag->setMargin(5);
    comboBox_tag->setFont(QFont("Datus",8,QFont::Bold,false));
    comboBox_tag->setMaximumHeight(100);
    vbox->addWidget(comboBox_tag);

    messageError_tag = new QLabel("");
    messageError_tag->setStyleSheet("color:red;");
    messageError_tag->setMargin(5);
    messageError_tag->setHidden(true);
    vbox->addWidget(messageError_tag);

    comboBox = new QComboBox;
    vbox->addWidget(comboBox);

    this->setMaximumHeight(50);
}

void DComboBox::setEditable(bool b)
{
    comboBox->setEditable(b);
}

void DComboBox::addItem(const QString &text)
{
    comboBox->addItem(text);
}

void DComboBox::setCompleter(QCompleter *c)
{
    comboBox->setCompleter(c);
}

void DComboBox::setModel(QAbstractItemModel *model)
{
    comboBox->setModel(model);
}

void DComboBox::setCurrentIndex(int index)
{
    comboBox->setCurrentIndex(index);
}

void DComboBox::setMessageError(QString msg)
{
    messageError_tag->setText(msg);
    messageError_tag->setHidden(false);
}

void DComboBox::setHiddenMessageError(bool hidden)
{
    messageError_tag->setHidden(hidden);
}

QString DComboBox::currentText()
{
    return comboBox->currentText();
}

int DComboBox::currentIndex()
{
    return comboBox->currentIndex();
}

QComboBox *DComboBox::getComboBox() const
{
    return comboBox;
}

