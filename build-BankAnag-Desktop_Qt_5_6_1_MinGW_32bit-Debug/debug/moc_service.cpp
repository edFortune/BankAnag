/****************************************************************************
** Meta object code from reading C++ file 'service.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_investissement/Service/service.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'service.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Service_t {
    QByteArrayData data[11];
    char stringdata0[220];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Service_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Service_t qt_meta_stringdata_Service = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Service"
QT_MOC_LITERAL(1, 8, 23), // "showDialogAddInvestment"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 21), // "onClickedServiceTable"
QT_MOC_LITERAL(4, 55, 32), // "insertIntoServiceInvestmentTable"
QT_MOC_LITERAL(5, 88, 24), // "insertIntoVersementTable"
QT_MOC_LITERAL(6, 113, 20), // "showDiagAddVersement"
QT_MOC_LITERAL(7, 134, 24), // "showContextVersementMenu"
QT_MOC_LITERAL(8, 159, 16), // "effacerVersement"
QT_MOC_LITERAL(9, 176, 25), // "showContextInvestmentMenu"
QT_MOC_LITERAL(10, 202, 17) // "effacerInvestment"

    },
    "Service\0showDialogAddInvestment\0\0"
    "onClickedServiceTable\0"
    "insertIntoServiceInvestmentTable\0"
    "insertIntoVersementTable\0showDiagAddVersement\0"
    "showContextVersementMenu\0effacerVersement\0"
    "showContextInvestmentMenu\0effacerInvestment"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Service[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    1,   60,    2, 0x08 /* Private */,
       4,    0,   63,    2, 0x08 /* Private */,
       5,    0,   64,    2, 0x08 /* Private */,
       6,    0,   65,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       8,    0,   69,    2, 0x08 /* Private */,
       9,    1,   70,    2, 0x08 /* Private */,
      10,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,

       0        // eod
};

void Service::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Service *_t = static_cast<Service *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showDialogAddInvestment(); break;
        case 1: _t->onClickedServiceTable((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->insertIntoServiceInvestmentTable(); break;
        case 3: _t->insertIntoVersementTable(); break;
        case 4: _t->showDiagAddVersement(); break;
        case 5: _t->showContextVersementMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 6: _t->effacerVersement(); break;
        case 7: _t->showContextInvestmentMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 8: _t->effacerInvestment(); break;
        default: ;
        }
    }
}

const QMetaObject Service::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Service.data,
      qt_meta_data_Service,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Service::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Service::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Service.stringdata0))
        return static_cast<void*>(const_cast< Service*>(this));
    return QWidget::qt_metacast(_clname);
}

int Service::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
