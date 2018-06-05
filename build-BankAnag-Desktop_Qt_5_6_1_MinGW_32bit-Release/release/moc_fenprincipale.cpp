/****************************************************************************
** Meta object code from reading C++ file 'fenprincipale.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BankAnag/fenprincipale.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenprincipale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Fenprincipale_t {
    QByteArrayData data[11];
    char stringdata0[142];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fenprincipale_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fenprincipale_t qt_meta_stringdata_Fenprincipale = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Fenprincipale"
QT_MOC_LITERAL(1, 14, 11), // "getPassword"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 16), // "closeDialogLogin"
QT_MOC_LITERAL(4, 44, 12), // "logOutDialog"
QT_MOC_LITERAL(5, 57, 11), // "creerCompte"
QT_MOC_LITERAL(6, 69, 11), // "creerBackUp"
QT_MOC_LITERAL(7, 81, 16), // "afficherSettings"
QT_MOC_LITERAL(8, 98, 16), // "closeFenSettings"
QT_MOC_LITERAL(9, 115, 21), // "dataFiresotreResponse"
QT_MOC_LITERAL(10, 137, 4) // "data"

    },
    "Fenprincipale\0getPassword\0\0closeDialogLogin\0"
    "logOutDialog\0creerCompte\0creerBackUp\0"
    "afficherSettings\0closeFenSettings\0"
    "dataFiresotreResponse\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fenprincipale[] = {

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
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    1,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   10,

       0        // eod
};

void Fenprincipale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Fenprincipale *_t = static_cast<Fenprincipale *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getPassword(); break;
        case 1: _t->closeDialogLogin(); break;
        case 2: _t->logOutDialog(); break;
        case 3: _t->creerCompte(); break;
        case 4: _t->creerBackUp(); break;
        case 5: _t->afficherSettings(); break;
        case 6: _t->closeFenSettings(); break;
        case 7: _t->dataFiresotreResponse((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Fenprincipale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Fenprincipale.data,
      qt_meta_data_Fenprincipale,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Fenprincipale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fenprincipale::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Fenprincipale.stringdata0))
        return static_cast<void*>(const_cast< Fenprincipale*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Fenprincipale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
