#ifndef DDATEEDIT_H
#define DDATEEDIT_H

#include <QWidget>
#include <QDateEdit>
#include <QLabel>

#include <QDate>

#include <QVBoxLayout>


class DDateEdit : public QWidget
{
    Q_OBJECT
public:
    explicit DDateEdit(QWidget *parent = 0);
    DDateEdit(QString tag);

    //QDateEdit functions
    void setCalendarPopup(bool enable);

    QDate date();


    void setCurrentDate();
    void setDate();
    void setDate(const QDate &date);

signals:

public slots:

private:
    QDateEdit *dateEdit;
    QLabel *dateEdt_tag;
};

#endif // DDATEEDIT_H
