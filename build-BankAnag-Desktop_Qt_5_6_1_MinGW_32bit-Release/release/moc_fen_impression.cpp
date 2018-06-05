/****************************************************************************
** Meta object code from reading C++ file 'fen_impression.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fen_impression/fen_impression.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fen_impression.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Fen_Impression_t {
    QByteArrayData data[8];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fen_Impression_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fen_Impression_t qt_meta_stringdata_Fen_Impression = {
    {
QT_MOC_LITERAL(0, 0, 14), // "Fen_Impression"
QT_MOC_LITERAL(1, 15, 5), // "print"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 9), // "QPrinter*"
QT_MOC_LITERAL(4, 32, 7), // "setZoom"
QT_MOC_LITERAL(5, 40, 8), // "closeFen"
QT_MOC_LITERAL(6, 49, 7), // "addText"
QT_MOC_LITERAL(7, 57, 9) // "filePrint"

    },
    "Fen_Impression\0print\0\0QPrinter*\0setZoom\0"
    "closeFen\0addText\0filePrint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fen_Impression[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    1,   42,    2, 0x0a /* Public */,
       5,    0,   45,    2, 0x0a /* Public */,
       6,    0,   46,    2, 0x0a /* Public */,
       7,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Fen_Impression::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Fen_Impression *_t = static_cast<Fen_Impression *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->print((*reinterpret_cast< QPrinter*(*)>(_a[1]))); break;
        case 1: _t->setZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->closeFen(); break;
        case 3: _t->addText(); break;
        case 4: _t->filePrint(); break;
        default: ;
        }
    }
}

const QMetaObject Fen_Impression::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Fen_Impression.data,
      qt_meta_data_Fen_Impression,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Fen_Impression::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fen_Impression::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Fen_Impression.stringdata0))
        return static_cast<void*>(const_cast< Fen_Impression*>(this));
    return QWidget::qt_metacast(_clname);
}

int Fen_Impression::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
