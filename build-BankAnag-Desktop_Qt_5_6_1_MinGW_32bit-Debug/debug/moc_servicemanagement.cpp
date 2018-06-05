/****************************************************************************
** Meta object code from reading C++ file 'servicemanagement.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_investissement/Service/servicemanagement.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'servicemanagement.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ServiceManagement_t {
    QByteArrayData data[5];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ServiceManagement_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ServiceManagement_t qt_meta_stringdata_ServiceManagement = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ServiceManagement"
QT_MOC_LITERAL(1, 18, 21), // "onActivatedListWidget"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 3), // "idx"
QT_MOC_LITERAL(4, 45, 9) // "fermerFen"

    },
    "ServiceManagement\0onActivatedListWidget\0"
    "\0idx\0fermerFen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ServiceManagement[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       4,    0,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QModelIndex,    3,
    QMetaType::Void,

       0        // eod
};

void ServiceManagement::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ServiceManagement *_t = static_cast<ServiceManagement *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onActivatedListWidget((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 1: _t->fermerFen(); break;
        default: ;
        }
    }
}

const QMetaObject ServiceManagement::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ServiceManagement.data,
      qt_meta_data_ServiceManagement,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ServiceManagement::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ServiceManagement::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ServiceManagement.stringdata0))
        return static_cast<void*>(const_cast< ServiceManagement*>(this));
    return QWidget::qt_metacast(_clname);
}

int ServiceManagement::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
