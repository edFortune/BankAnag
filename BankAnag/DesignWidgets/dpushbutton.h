#ifndef DPUSHBUTTON_H
#define DPUSHBUTTON_H

#include <QPushButton>


class DPushButton : public QPushButton
{
public:
    DPushButton(QWidget *parent);
    DPushButton(const QString &text);
    DPushButton(const QString &text, QWidget *parent);

    void setCustomStyleSheet(const QString style);
};

#endif // DPUSHBUTTON_H
