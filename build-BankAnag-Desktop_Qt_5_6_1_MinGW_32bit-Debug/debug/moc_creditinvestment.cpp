/****************************************************************************
** Meta object code from reading C++ file 'creditinvestment.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_investissement/Produit/creditinvestment.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'creditinvestment.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreditInvestment_t {
    QByteArrayData data[8];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreditInvestment_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreditInvestment_t qt_meta_stringdata_CreditInvestment = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CreditInvestment"
QT_MOC_LITERAL(1, 17, 26), // "onDoubleClickedTableCredit"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 21), // "onClickedAddVersement"
QT_MOC_LITERAL(4, 67, 21), // "showContextMenuCredit"
QT_MOC_LITERAL(5, 89, 13), // "effacerCredit"
QT_MOC_LITERAL(6, 103, 24), // "showContextMenuVersement"
QT_MOC_LITERAL(7, 128, 16) // "effacerVersement"

    },
    "CreditInvestment\0onDoubleClickedTableCredit\0"
    "\0onClickedAddVersement\0showContextMenuCredit\0"
    "effacerCredit\0showContextMenuVersement\0"
    "effacerVersement"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreditInvestment[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       3,    0,   47,    2, 0x08 /* Private */,
       4,    1,   48,    2, 0x08 /* Private */,
       5,    0,   51,    2, 0x08 /* Private */,
       6,    1,   52,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,

       0        // eod
};

void CreditInvestment::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreditInvestment *_t = static_cast<CreditInvestment *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onDoubleClickedTableCredit((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->onClickedAddVersement(); break;
        case 2: _t->showContextMenuCredit((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: _t->effacerCredit(); break;
        case 4: _t->showContextMenuVersement((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 5: _t->effacerVersement(); break;
        default: ;
        }
    }
}

const QMetaObject CreditInvestment::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CreditInvestment.data,
      qt_meta_data_CreditInvestment,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreditInvestment::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreditInvestment::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreditInvestment.stringdata0))
        return static_cast<void*>(const_cast< CreditInvestment*>(this));
    return QWidget::qt_metacast(_clname);
}

int CreditInvestment::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
