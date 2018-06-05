/****************************************************************************
** Meta object code from reading C++ file 'fournisseur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_investissement/Produit/fournisseur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fournisseur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Fournisseur_t {
    QByteArrayData data[5];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fournisseur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fournisseur_t qt_meta_stringdata_Fournisseur = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Fournisseur"
QT_MOC_LITERAL(1, 12, 16), // "onClickedAddToDB"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 23), // "onClickedAddFournisseur"
QT_MOC_LITERAL(4, 54, 25) // "onClickedTableFournisseur"

    },
    "Fournisseur\0onClickedAddToDB\0\0"
    "onClickedAddFournisseur\0"
    "onClickedTableFournisseur"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fournisseur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    1,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    2,

       0        // eod
};

void Fournisseur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Fournisseur *_t = static_cast<Fournisseur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onClickedAddToDB(); break;
        case 1: _t->onClickedAddFournisseur(); break;
        case 2: _t->onClickedTableFournisseur((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Fournisseur::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Fournisseur.data,
      qt_meta_data_Fournisseur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Fournisseur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fournisseur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Fournisseur.stringdata0))
        return static_cast<void*>(const_cast< Fournisseur*>(this));
    return QWidget::qt_metacast(_clname);
}

int Fournisseur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
