/****************************************************************************
** Meta object code from reading C++ file 'produitinvestments.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_investissement/Produit/produitinvestments.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'produitinvestments.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProduitInvestments_t {
    QByteArrayData data[11];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProduitInvestments_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProduitInvestments_t qt_meta_stringdata_ProduitInvestments = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ProduitInvestments"
QT_MOC_LITERAL(1, 19, 20), // "onChangeProduitIndex"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 3), // "val"
QT_MOC_LITERAL(4, 45, 21), // "onChangeInvesterIndex"
QT_MOC_LITERAL(5, 67, 22), // "onChangeTypePayerIndex"
QT_MOC_LITERAL(6, 90, 22), // "onValuePrixAchatChange"
QT_MOC_LITERAL(7, 113, 22), // "onValuePrixVenteChange"
QT_MOC_LITERAL(8, 136, 21), // "onValueQteAchatChange"
QT_MOC_LITERAL(9, 158, 22), // "onValueMtntVerstChange"
QT_MOC_LITERAL(10, 181, 24) // "onClickedAjoutInvestment"

    },
    "ProduitInvestments\0onChangeProduitIndex\0"
    "\0val\0onChangeInvesterIndex\0"
    "onChangeTypePayerIndex\0onValuePrixAchatChange\0"
    "onValuePrixVenteChange\0onValueQteAchatChange\0"
    "onValueMtntVerstChange\0onClickedAjoutInvestment"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProduitInvestments[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    1,   57,    2, 0x08 /* Private */,
       5,    1,   60,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       8,    1,   69,    2, 0x08 /* Private */,
       9,    1,   72,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    3,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,

       0        // eod
};

void ProduitInvestments::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProduitInvestments *_t = static_cast<ProduitInvestments *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onChangeProduitIndex((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onChangeInvesterIndex((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onChangeTypePayerIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onValuePrixAchatChange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: _t->onValuePrixVenteChange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 5: _t->onValueQteAchatChange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->onValueMtntVerstChange((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->onClickedAjoutInvestment(); break;
        default: ;
        }
    }
}

const QMetaObject ProduitInvestments::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProduitInvestments.data,
      qt_meta_data_ProduitInvestments,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProduitInvestments::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProduitInvestments::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProduitInvestments.stringdata0))
        return static_cast<void*>(const_cast< ProduitInvestments*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProduitInvestments::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
