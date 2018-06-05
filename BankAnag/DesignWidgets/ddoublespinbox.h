#ifndef DDOUBLESPINBOX_H
#define DDOUBLESPINBOX_H

#include <QWidget>
#include <QDoubleSpinBox>
#include <QLabel>

#include <QVBoxLayout>

class DDoubleSpinBox : public QWidget
{
    Q_OBJECT
public:
    explicit DDoubleSpinBox(QWidget *parent = 0);
    DDoubleSpinBox(const QString tag);

    double value();

    void setValue(double val);
    void setMinimum(double min);
    void setMaximum(double max);

    void setMessageError(QString msg);
    void setHiddenMessageError(bool hidden);

    QDoubleSpinBox *getDoubleSpinBox() const;

signals:

public slots:

private:
    QDoubleSpinBox *doubleSpinBox;
    QLabel *doubleSpinBox_tag;
    QLabel *messageError_tag;
};

#endif // DDOUBLESPINBOX_H
