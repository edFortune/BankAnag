/****************************************************************************
** Meta object code from reading C++ file 'produittransaction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_investissement/Produit/produittransaction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'produittransaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ProduitTransaction_t {
    QByteArrayData data[14];
    char stringdata0[216];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProduitTransaction_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProduitTransaction_t qt_meta_stringdata_ProduitTransaction = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ProduitTransaction"
QT_MOC_LITERAL(1, 19, 11), // "onEnterItem"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 29), // "onItemModelTransactionChanged"
QT_MOC_LITERAL(4, 62, 14), // "QStandardItem*"
QT_MOC_LITERAL(5, 77, 22), // "onValueDiscountChanged"
QT_MOC_LITERAL(6, 100, 18), // "onClickMenuContext"
QT_MOC_LITERAL(7, 119, 10), // "deleteItem"
QT_MOC_LITERAL(8, 130, 20), // "onClickedTakePayment"
QT_MOC_LITERAL(9, 151, 20), // "onClickedSavePayment"
QT_MOC_LITERAL(10, 172, 9), // "fermerFen"
QT_MOC_LITERAL(11, 182, 22), // "insertIntoSalesDetails"
QT_MOC_LITERAL(12, 205, 2), // "id"
QT_MOC_LITERAL(13, 208, 7) // "idxItem"

    },
    "ProduitTransaction\0onEnterItem\0\0"
    "onItemModelTransactionChanged\0"
    "QStandardItem*\0onValueDiscountChanged\0"
    "onClickMenuContext\0deleteItem\0"
    "onClickedTakePayment\0onClickedSavePayment\0"
    "fermerFen\0insertIntoSalesDetails\0id\0"
    "idxItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProduitTransaction[] = {

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
       1,    1,   59,    2, 0x08 /* Private */,
       3,    1,   62,    2, 0x08 /* Private */,
       5,    1,   65,    2, 0x08 /* Private */,
       6,    1,   68,    2, 0x08 /* Private */,
       7,    0,   71,    2, 0x08 /* Private */,
       8,    0,   72,    2, 0x08 /* Private */,
       9,    0,   73,    2, 0x08 /* Private */,
      10,    0,   74,    2, 0x08 /* Private */,
      11,    2,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,

       0        // eod
};

void ProduitTransaction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ProduitTransaction *_t = static_cast<ProduitTransaction *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onEnterItem((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onItemModelTransactionChanged((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 2: _t->onValueDiscountChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->onClickMenuContext((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 4: _t->deleteItem(); break;
        case 5: _t->onClickedTakePayment(); break;
        case 6: _t->onClickedSavePayment(); break;
        case 7: _t->fermerFen(); break;
        case 8: _t->insertIntoSalesDetails((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject ProduitTransaction::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ProduitTransaction.data,
      qt_meta_data_ProduitTransaction,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ProduitTransaction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProduitTransaction::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ProduitTransaction.stringdata0))
        return static_cast<void*>(const_cast< ProduitTransaction*>(this));
    return QWidget::qt_metacast(_clname);
}

int ProduitTransaction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
