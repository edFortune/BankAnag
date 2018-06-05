#ifndef DLINEEDIT_H
#define DLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>

class DLineEdit : public QWidget
{
public:
    DLineEdit(QWidget *parent);
    DLineEdit(QString tag);

    QString text();

    //Functions that return none
    void clear();
    void setCompleter(QCompleter *completer);
    void setText(const QString &);

    //Functions that return sthg
    QString text() const;

    QLineEdit *getLineEdit() const;
private:
    QLineEdit *lineEdit;
    QLabel *lineEdit_tag;

};

#endif // DLINEEDIT_H
