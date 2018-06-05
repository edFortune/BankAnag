#ifndef DTEXTEDIT_H
#define DTEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QLabel>

#include <QVBoxLayout>

class DTextEdit : public QWidget
{
    Q_OBJECT
public:
    explicit DTextEdit(QWidget *parent = 0);
    DTextEdit(QString tag);

    QString toPlainText();

    void setMessageError(QString msg);
    void setHiddenMessageError(bool hidden);

    void clear();

signals:

public slots:

private:
    QTextEdit *textEdit;
    QLabel *textEdit_tag;
    QLabel *messageError_tag;

};

#endif // DTEXTEDIT_H
