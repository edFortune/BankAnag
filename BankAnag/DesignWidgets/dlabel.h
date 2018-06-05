#ifndef DLABEL_H
#define DLABEL_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLocale>

class DLabel : public QWidget
{
    Q_OBJECT
public:
    explicit DLabel(QWidget *parent = 0);
    DLabel(const QString tag);
    DLabel(const QString tag, const int alignmentLabel);

    void setText(const QString &);
    QString text() const;
    void setColor(const QString &color);
    void setBold(bool);
    void setTextFromInt(int);
    void setTextFromDouble(double);
    void setPriceTextFromDouble(QString currency,double amount);
    void setTextFromDoubleToInt(double);


    //Public variables
public:
    static const int AlignLabelTop = 200;
    static const int AlignLabelLeft = 400;

signals:

public slots:

    //Private functions
private:
    void setConstructorAlignLabelTop(const QString tag);
    void setConstructorAlignLabelLeft(const QString tag);

private:
    QLabel *label_tag;
    QLabel *label;

    bool isNumberShort;
    bool isNumberLocalEnglish;
};

#endif // DLABEL_H
