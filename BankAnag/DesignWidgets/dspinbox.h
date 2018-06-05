#ifndef DSPINBOX_H
#define DSPINBOX_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>

#include <QVBoxLayout>

class DSpinBox : public QWidget
{
    Q_OBJECT
public:
    explicit DSpinBox(QWidget *parent = 0);
    DSpinBox(const QString tag);

    int value();
signals:

public slots:

private:
    QLabel *spinBox_tag;
    QSpinBox *spinBox;
};

#endif // DSPINBOX_H
