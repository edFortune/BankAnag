#ifndef DCOMBOBOX_H
#define DCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>

#include <QCompleter>

#include <QVBoxLayout>

class DComboBox : public QWidget
{
    Q_OBJECT
public:
    explicit DComboBox(QWidget *parent = 0);
    DComboBox(QString tag);

    void setEditable(bool);
    void addItem(const QString &text);
    void setCompleter(QCompleter *c);
    void setModel(QAbstractItemModel *model);
    void setCurrentIndex(int index);

    void setMessageError(QString msg);
    void setHiddenMessageError(bool hidden);

    QString currentText();
    int currentIndex();


    //Private functions
    QComboBox *getComboBox() const;

private:


signals:


public slots:


private:
    QLabel *comboBox_tag;
    QLabel *messageError_tag;
    QComboBox *comboBox;
};

#endif // DCOMBOBOX_H
