#ifndef SERVICEINVESTMENTS_H
#define SERVICEINVESTMENTS_H

#include <QWidget>
#include <QGridLayout>

#include "DesignWidgets/dlineedit.h"
#include "DesignWidgets/ddateedit.h"
#include "DesignWidgets/dgroupbox.h"
#include "DesignWidgets/dcombobox.h"

class ServiceInvestments : public QWidget
{
    Q_OBJECT
public:
    explicit ServiceInvestments(QWidget *parent = 0);

signals:

public slots:
};

#endif // SERVICEINVESTMENTS_H
